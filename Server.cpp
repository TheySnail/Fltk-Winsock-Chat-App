#include "Server.h"

Server::Server() : Timer(0.0167f), m_server(8080)
{
	this->StartTimer();
}

Server::~Server()
{

}

void Server::on_tick()
{
	//printf("tick");
	std::shared_ptr<ClientSocket> client = m_server.accept();

	if (client)
	{
		printf("CLinet Connect!\n");
		clients.push_back(client);
	}


	for (size_t ci = 0; ci < clients.size(); ++ci)
	{
		std::string message;

		while (clients.at(ci)->receive(message))
		{
			printf("Message recived: \n %s\n", message.c_str());

			for (size_t cii = 0; cii < clients.size(); ++cii)
			{
				clients.at(cii)->send(message.c_str());
			}
		}

		

		if (clients.at(ci)->m_closed)
		{
			printf("Client Disconnected\n");
			clients.erase(clients.begin() + ci);
			ci--;
		}
		
	}
}