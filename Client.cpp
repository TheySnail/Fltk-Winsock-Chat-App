#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include "Client.h"
#include <iostream>
#include <FL/Fl_ask.h>

Client::Client(MainWindow* _MainWindowPtr) :
	Timer(0.0167f)
	, m_Port(8080)
	, m_ServerIPAdrr("")
	, m_MainWindowPtr(nullptr)
{
	m_MainWindowPtr = _MainWindowPtr;
	std::cout << "w";
}

Client::~Client()
{
}

void Client::InputIpAddr(std::string _IpAddr)
{

	m_ServerIPAdrr = _IpAddr;
	std::cout << m_ServerIPAdrr << std::endl;


	m_ClientSocket = std::make_shared<ClientSocket>(_IpAddr, m_Port);
	this->StartTimer();
}

void Client::ClientSend(std::string _Message)
{
	m_ClientSocket->send(_Message);
}

void Client::on_tick()
{
	/*std::string buffer1;

	std::cout << std::endl << "Enter the message: ";
	std::getline(std::cin, buffer1);

	m_ClientSocket->send(buffer1);*/

	//recieve incoming data


	std::string buffer;
	if (m_ClientSocket->receive(buffer))
	{
		std::cout << buffer;

		m_MainWindowPtr->AddToDisplay(buffer);
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