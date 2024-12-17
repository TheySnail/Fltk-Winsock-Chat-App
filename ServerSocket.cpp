#include "ServerSocket.h"

#include <WS2tcpip.h>
#include <stdexcept>
#include <string>
#include <vector>

ServerSocket::ServerSocket(int _port)
	: m_Socket(INVALID_SOCKET)//null socket
{
	//what we want the socket to use
	addrinfo hints = { 0 };
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	addrinfo* result = NULL;

	if (getaddrinfo(NULL, std::to_string(_port).c_str(), &hints, &result) != 0)
	{
		throw std::runtime_error("Failed to resolve server address or port");
	}

	m_Socket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);

	if (m_Socket == INVALID_SOCKET)
	{
		freeaddrinfo(result);
		throw std::runtime_error("Failed to create socket");
	}

	if (bind(m_Socket, result->ai_addr, result->ai_addrlen) == SOCKET_ERROR)
	{
		freeaddrinfo(result);
		throw std::runtime_error("Failed to bind socket");
	}

	freeaddrinfo(result);

	if (listen(m_Socket, SOMAXCONN) == SOCKET_ERROR)
	{
		throw std::runtime_error("Failed to listen on socket");
	}

	u_long mode = 1;

	if (ioctlsocket(m_Socket, FIONBIO, &mode) == SOCKET_ERROR)
	{
		throw std::runtime_error("Failed to set non-blocking");
	}
}

ServerSocket::~ServerSocket()
{
	closesocket(m_Socket);
}

std::shared_ptr<ClientSocket> ServerSocket::accept()
{
	SOCKET socket = ::accept(m_Socket, NULL, NULL);

	if (socket == INVALID_SOCKET)
	{
		if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			throw std::runtime_error("Failed to accept socket");
		}

		return std::shared_ptr<ClientSocket>();
	}

	std::shared_ptr<ClientSocket> rtn = std::make_shared<ClientSocket>();
	rtn->m_Socket = socket;

	return rtn;
}
