#pragma once
#include "ClientSocket.h"
#include "ServerSocket.h"
#include "Timer.h"
#include <vector>

class Server : public Timer
{
public:
	Server();
	~Server();

private:
	std::vector<std::shared_ptr<ClientSocket> > clients;
	ServerSocket m_server;
	void on_tick();
};