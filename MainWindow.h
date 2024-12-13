#pragma once
#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H


#include "Timer.h"
#include "Server.h"
#include "Client.h"
#include "MainWindowLayout.h"


class  Client;


class MainWindow : public MainWindowLayout
{

public: 
	MainWindow();
	void AddToDisplay(std::string _buffer);

private:
	//button functions
	static void CreateServer(Fl_Widget* _widget, void* _userData);
	static void StaticCreateClient(Fl_Widget* _widget, void* _userData);
	void CreateClient();
	static void ConfirmIp(Fl_Widget* _widget, void* _userData);

	static void StaticSendUserMessage(Fl_Widget* _widget, void* _userData);
	void SendUserMessage();


	bool m_ServerActive;

	std::shared_ptr<Server> m_Server;
	std::shared_ptr<Client> m_Client;
};



#endif // !_WINDOW_H
