#pragma once
#ifndef _MAIN_WINDOW_H
#define _MAIN_WINDOW_H


#include "Timer.h"
#include "Server.h"
#include "Client.h"
#include "MainWindowLayout.h"
#include "message.h"

class Client;
class Message;

class MainWindow : public MainWindowLayout
{

public: 
	MainWindow();
	void AddToDisplay(std::string _buffer);

	std::string getUsername();

private:
	//button functions
	static void CreateServer(Fl_Widget* _widget, void* _userData);
	static void StaticCreateClient(Fl_Widget* _widget, void* _userData);
	void CreateClient();

	static void StaticConfirmIp(Fl_Widget* _widget, void* _userData);

	static void StaticSendUserMessage(Fl_Widget* _widget, void* _userData);
	void SendUserMessage();

	static void Close(Fl_Widget* _widget, void* _userData);

	static void StaticReturnToMainMenu(Fl_Widget* _widget, void* _userData);
	void ReturnToMainMenu();

	std::string HandleIncomingXML(std::string _IncomingXML);

	static void ChangeToLight(Fl_Widget* _widget, void* _userData);
	static void ChangeToDark(Fl_Widget* _widget, void* _userData);
	static void ChangeToBird(Fl_Widget* _widget, void* _userData);

	bool m_ServerActive;

	std::shared_ptr<Server> m_Server;
	std::shared_ptr<Client> m_Client;

	std::string m_Username;
};



#endif // !_WINDOW_H
