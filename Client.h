#pragma once

#include "Wsa.h"
#include "ServerSocket.h"
#include <iostream>
#include <vector>
#include <string>
#include "Timer.h"
#include <WinSock2.h>

class Client :public Timer
{
public:
	Client();
	~Client();

	void InputIpAddr(std::string _IpAddr);
	//int ClientConnect();
private:
	
	void on_tick();
	int m_Port;
	SOCKET m_ClientSocketBackup;

	std::string m_ServerIPAdrr;

	std::shared_ptr<ClientSocket> m_ClientSocket;

	std::vector<unsigned char> m_IncomingData;
	//std::string m_IncomingData;
};