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
	std::vector<std::shared_ptr<ClientSocket> > m_Clients;
	ServerSocket m_Server;
	void on_tick();
};