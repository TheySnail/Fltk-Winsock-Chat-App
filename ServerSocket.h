#pragma once
#ifndef SERVERSOCKET_H_
#define SERVERSOCKET_H_

#include <WinSock2.h>
#include "ClientSocket.h"
#include <iostream>

struct ServerSocket
{
	ServerSocket(int _port);
	~ServerSocket();

	std::shared_ptr<ClientSocket> accept();

private:
	SOCKET m_socket;

	ServerSocket(const ServerSocket& _copy);
	ServerSocket& operator = (const ServerSocket& _assign);
};


#endif // !SEVERSOCKET_H_
