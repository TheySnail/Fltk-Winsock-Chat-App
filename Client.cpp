#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Client.h"
#include <iostream>
#include <FL/Fl_ask.h>

Client::Client() :
	Timer(0.0167f)
	, m_ClientSocketBackup(INVALID_SOCKET)
	, m_Port(8080)
	, m_ServerIPAdrr("")
{

}

Client::~Client()
{
	closesocket(m_ClientSocketBackup);
}

void Client::InputIpAddr(std::string _IpAddr)
{
	int isConnected;

	m_ServerIPAdrr = _IpAddr;
	std::cout << m_ServerIPAdrr << std::endl;

	/*isConnected = this->ClientConnect();

	return isConnected;*/

	m_ClientSocket = std::make_shared<ClientSocket>(_IpAddr, m_Port);
	this->StartTimer();
}

//int Client::ClientConnect()
//{
//	//create socket
//	m_ClientSocketBackup = INVALID_SOCKET;
//	m_ClientSocketBackup = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//
//	if (m_ClientSocketBackup == INVALID_SOCKET)
//	{
//		std::cout << "error at socket: " << WSAGetLastError() << std::endl;
//		return 0;
//	}
//
//
//	// Connect to the server
//	sockaddr_in clientService;
//	clientService.sin_family = AF_INET;
//	clientService.sin_port = htons(m_Port);  // Use the same port as the server
//	 
//	std::cout << "trying to conenct to ip address " << m_ServerIPAdrr << std::endl;
//	clientService.sin_addr.s_addr = inet_addr(m_ServerIPAdrr.c_str());//server ip address
//
//	// Use the connect function
//	if (connect(m_ClientSocketBackup, reinterpret_cast<SOCKADDR*>(&clientService), sizeof(clientService)) == SOCKET_ERROR)
//	{
//		std::cout << "Client: connect() - Failed to connect: " << WSAGetLastError() << std::endl;
//
//		fl_alert("Invalid IP Address Inputed");
//
//		return 0;
//	}
//	else
//	{
//		std::cout << "client connected" << std::endl;
//		
//		this->StartTimer();
//
//		return 1;
//	}
//}

void Client::on_tick()
{
	std::string buffer1;

	std::cout << std::endl << "Enter the message: ";
	std::getline(std::cin, buffer1);

	m_ClientSocket->send(buffer1);

	//recieve incoming data
	/*std::vector<unsigned char> buffer(1024);

	while (true)
	{
		
		int bytes = m_ClientSocket->receive(buffer);
		if (!bytes)
		{
			break;
		}
		m_IncomingData.insert(m_IncomingData.end(), buffer.begin(), buffer.begin() + bytes);
	}

	for (size_t ci = 0; ci < m_IncomingData.size(); ++ci)
	{

		if (m_IncomingData.at(ci) == '\n')
		{
			std::cout << m_IncomingData[ci];
		}
	}*/

	std::string buffer;
	if (m_ClientSocket->receive(buffer))
	{
		std::cout << buffer;

		/*textbuffer.append(buffer);	how to display text onto wdiget
		textbuffer.append(\n);
		display text buffer*/
	}

	//use fltk display to show message
}


//put this aroud functions to catch erros and throw a box in fltk to not crash 
//
// #include <FL/Fl_ask.h>
// 
//try
//{
//	function();
//}
//catch (std::exception& _e)
//{
//	std::string msg = _e.what();
//	fl_alert(msg.c_str());
//}