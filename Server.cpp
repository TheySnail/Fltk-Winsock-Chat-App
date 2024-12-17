#include "Server.h"

Server::Server() : Timer(0.0167f), m_Server(8080)
{
	this->StartTimer();
}

Server::~Server()
{

}

void Server::on_tick()
{
	//printf("tick");
	std::shared_ptr<ClientSocket> client = m_Server.accept();

	if (client)
	{
		printf("CLinet Connect!\n");
		m_Clients.push_back(client);
	}


	for (size_t ci = 0; ci < m_Clients.size(); ++ci)
	{
		std::string message;

		while (m_Clients.at(ci)->receive(message))
		{
			if (message.at(0) == '©')//symbol rep request for server info
			{
				m_Clients.at(ci)->send("©Server version : v1.2.3 \nAmount of clients connect " + std::to_string(m_Clients.size()));//send to only client that requested
			}
			else
			{
				printf("Message recived: \n %s\n", message.c_str());

				for (size_t cii = 0; cii < m_Clients.size(); ++cii)
				{
					m_Clients.at(cii)->send(message.c_str());
				}
			}
			
		}

		

		if(m_Clients.at(ci)->m_Closed)
		{
			for (size_t cii = 0; cii < m_Clients.size(); ++cii)
			{
				m_Clients.at(cii)->send("Pyvrag qvfpbaarpgrq\n");// this is hardcoded into rot13 itll be the same each time so it doesnt really matter
			}
			m_Clients.erase(m_Clients.begin() + ci);
			ci--;
		}
	}

}