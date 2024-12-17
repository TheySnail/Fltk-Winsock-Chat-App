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
	void SetClientConnected(bool _Status);

	std::string getUsername();
	std::string Rot13(std::string _message);

	void ReturnToMainMenu();

private:
	//button functions
	static void StaticCreateServer(Fl_Widget* _widget, void* _userData);
	void CreateServer();

	static void StaticCreateClient(Fl_Widget* _widget, void* _userData);
	void CreateClient();

	static void StaticConfirmIp(Fl_Widget* _widget, void* _userData);

	static void StaticSendUserMessage(Fl_Widget* _widget, void* _userData);
	void SendUserMessage();

	static void Close(Fl_Widget* _widget, void* _userData);

	static void StaticReturnToMainMenu(Fl_Widget* _widget, void* _userData);
	

	static void ShowChangeUsernameBox(Fl_Widget* _widget, void* _userData);

	static void GetNewUsername(Fl_Widget* _widget, void* _userData);

	std::string HandleIncomingXML(std::string _IncomingXML);

	static void ChangeToLight(Fl_Widget* _widget, void* _userData);
	static void ChangeToDark(Fl_Widget* _widget, void* _userData);
	static void ChangeToBird(Fl_Widget* _widget, void* _userData);
	static void ChangeToBlossom(Fl_Widget* _widget, void* _userData);
	static void ChangeToBeige(Fl_Widget* _widget, void* _userData);
	static void ChangeToHacker(Fl_Widget* _widget, void* _userData);

	static void ShowAboutInfo(Fl_Widget* _widget, void* _userData);

	void ResizeWindow();

	static void RequestSeverData(Fl_Widget* _widget, void* _userData);


	bool m_ServerActive;

	std::shared_ptr<Server> m_Server;
	std::shared_ptr<Client> m_Client;

	std::string m_Username;
	bool m_HasAdmin;
	bool m_AboutBoxShown;
	bool m_ServerInfoBoxShown;
	bool m_ClientConnected;
};



#endif // !_WINDOW_H
