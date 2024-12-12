#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "ClientSocket.h"
#include "ServerSocket.h"
#include <iostream>
#include <string>

ClientSocket::ClientSocket()
	: m_socket(INVALID_SOCKET)
	, m_closed(false)
{
	
}

ClientSocket::ClientSocket(std::string _IpAddr, int _port)
	: m_socket(INVALID_SOCKET)
	, m_closed(false)
{
	//create socket
	m_socket = INVALID_SOCKET;
	m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_socket == INVALID_SOCKET)
	{
		std::cout << "error at socket: " << WSAGetLastError() << std::endl;
	}


	// Connect to the server
	sockaddr_in clientService;
	clientService.sin_family = AF_INET;
	clientService.sin_port = htons(_port);  // Use the same port as the server

	std::cout << "trying to conenct to ip address " << _IpAddr << std::endl;
	clientService.sin_addr.s_addr = inet_addr(_IpAddr.c_str());//server ip address

	// Use the connect function
	if (connect(m_socket, reinterpret_cast<SOCKADDR*>(&clientService), sizeof(clientService)) == SOCKET_ERROR)
	{
		std::cout << "Client: connect() - Failed to connect: " << WSAGetLastError() << std::endl;

		//fl_alert("Invalid IP Address Inputed");

	}
	else
	{
		std::cout << "client connected" << std::endl;

		//this->StartTimer();
	}

	u_long mode = 1;

	if (ioctlsocket(m_socket, FIONBIO, &mode) == SOCKET_ERROR)
	{
		throw std::runtime_error("Failed to set non-blocking");
	}
}


ClientSocket::~ClientSocket()
{
	if (m_socket != INVALID_SOCKET)
	{
		closesocket(m_socket);
	}
}

bool ClientSocket::receive(std::string& _message)
{
	char buffer[256] = { 0 };
	int bytes = ::recv(m_socket, buffer, sizeof(buffer)-1 , 0);
	if (bytes == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			throw std::runtime_error("Read failed");
		}

		return false;
	}
	else if (bytes == 0)
	{
		m_closed = true;
		return false;
	}
	_message = buffer;
	return true;

}

int ClientSocket::send(const std::string& _message)
{
	int bytes = ::send(m_socket, _message.c_str(), _message.length(), 0);
	if (bytes <= 0)
	{
		throw std::runtime_error("Failed to send data");
		return 0;
	}
	return bytes;
}

