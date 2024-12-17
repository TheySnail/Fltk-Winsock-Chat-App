#pragma once

#include "Wsa.h"
#include "ServerSocket.h"
#include <iostream>
#include <vector>
#include <string>
#include "Timer.h"
#include <WinSock2.h>

#include "MainWindow.h"

class MainWindow;

class Client :public Timer
{
public:
	Client(MainWindow* _MainWindowPtr);
	~Client();

	void InputIpAddr(std::string _IpAddr);
	void ClientSend(std::string _Message);

	void RequestServerInfo();

	bool GetClientSocketClosed();

protected:
	std::shared_ptr<ClientSocket> m_ClientSocket;

private:
	
	void on_tick();
	int m_Port;

	std::string m_ServerIPAdrr;

	

	std::vector<unsigned char> m_IncomingData;

	MainWindow* m_MainWindowPtr;
};