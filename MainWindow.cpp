#include "MainWindow.h"
#include <stdexcept>

#include "Server.h"
#include <FL/Fl_ask.h>

#include "message.h"

MainWindow::MainWindow()
	: m_Server(nullptr)
	, m_Client(nullptr)
	, m_ServerActive(false)
	, m_Username("Temp")

{	


	m_CreateServerBttn.callback(CreateServer, this);
	m_CreateClientBttn.callback(StaticCreateClient, this);
	m_IpConfirmBttn.callback(StaticConfirmIp, this);
	m_MessageSendBttn.callback(StaticSendUserMessage, this);

	m_menuBar.add("&File/&Return To Menu", "^o", StaticReturnToMainMenu, this);
	m_menuBar.add("&File/&Save", "^s", NULL,0, FL_MENU_DIVIDER);
	m_menuBar.add("&File/&Exit", "^e", Close, this);
	m_menuBar.add("&Theme/&Light", NULL, ChangeToLight, this);
	m_menuBar.add("&Theme/&Dark", NULL, ChangeToDark, this);
	m_menuBar.add("&Theme/&Bird", NULL, ChangeToBird, this);

	ChangeLayout(MainMenu);
}

void MainWindow::CreateServer(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;

	if (mw->m_ServerActive == false)
	{
		mw->m_Server = std::make_shared<Server>();
		std::cout << "server created" << std::endl;

		mw->m_ServerActive = true;

		mw->ChangeLayout(ServerScreen);
	}

	else
	{
		std::cout << "server already active" << std::endl;
	}
	
}

//having a static and non static version of a function allows me to get around the weird fltk callback limitations
void MainWindow::StaticCreateClient(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;

	mw->CreateClient();
}

void MainWindow::CreateClient()
{
	m_Client = std::make_shared<Client>(this);

	ChangeLayout(ClientIpScreen);
}

void MainWindow::StaticConfirmIp(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	try
	{
		std::string IpBuffer;

		IpBuffer = mw->m_IpInputBox.value();

		mw->m_IpInputBox.value("");

		mw->m_Client->InputIpAddr(IpBuffer);

		if (mw->m_UsernameInputBox.value() != "")
		{
			mw->m_Username = mw->m_UsernameInputBox.value();
		}

	}
	catch (std::exception& _e)
	{
		std::string msg = _e.what();
		fl_alert(msg.c_str());
	}
	
}


void MainWindow::StaticSendUserMessage(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	mw->SendUserMessage();
}

void MainWindow::SendUserMessage()
{
	std::string buffer;
	buffer = m_MessageInput.value();

	std::shared_ptr <Message>m_MessagePtr;

	m_MessagePtr = std::make_shared<Message>(m_Username, m_MessageInput.value());

	m_Client->ClientSend(m_MessagePtr->ConvertXMLtoString());//sends the converted xml doc as a string
}

void MainWindow::AddToDisplay(std::string _buffer)
{
	//m_textBuffer.append(_buffer.c_str());

	m_textBuffer.append((HandleIncomingXML(_buffer)).c_str());//passes in the handled incoming xml data as a c string so it can be displayed in text display

	m_textDisplay.buffer(m_textBuffer);

}

void MainWindow::Close(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	mw->hide();
}

void MainWindow::StaticReturnToMainMenu(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	mw->ReturnToMainMenu();
}

void MainWindow::ReturnToMainMenu()
{
	//set the points to the client and server to null destroying them
	this->m_Server = nullptr;
	this->m_Client = nullptr;
	
	this->m_ServerActive = false; //make it so user can create new server if they want

	this->ChangeLayout(MainMenu);// go back to main menu screen

}


std::string MainWindow::getUsername()
{
	return m_Username;
}


std::string MainWindow::HandleIncomingXML(std::string _IncomingXML)
{
	pugi::xml_document tempdoc;

	tempdoc.load_string(_IncomingXML.c_str());//pareses the incoming string back into usable xml

	pugi::xml_node UserData = tempdoc.child("UserData");//creates the root node of incoming xml so i can access it here

	std::string username = UserData.child("Info").child("Username").attribute("Username").value();

	std::string message = UserData.child("Info").child("Message").attribute("Message").value();

	std::string Everyone = "Everyone";//needs to be string so i can compare value of Reciprocant

	//if targeted to this specific user will show for targeted user AND user who sent it so they can see whisper history
	if ((UserData.child("Info").child("Reciprocant").attribute("Reciprocant").value() == getUsername()) || (UserData.child("Info").child("Username").attribute("Username") .value() == getUsername() && UserData.child("Info").child("Reciprocant").attribute("Reciprocant").value() != Everyone))
	{
		std::string completeMessage = username + " whispered to " + UserData.child("Info").child("Reciprocant").attribute("Reciprocant").value() + ": " + message + "\n";
		//displays as
		// user 1 Whispered to user 2 : Message
		return completeMessage;
	}

	//if tartgeted to everyone
	else if (UserData.child("Info").child("Reciprocant").attribute("Reciprocant").value() == Everyone)
	{
		std::string completeMessage = username + ": " + message + "\n";
		return completeMessage;
	}

	//if targeted to a user which is not this one
	else
	{
		return "";
	}
}


void MainWindow::ChangeToLight(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	mw->ChangeTheme(Light);
}

void MainWindow::ChangeToDark(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	mw->ChangeTheme(Dark);
}

void MainWindow::ChangeToBird(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	mw->ChangeTheme(Bird);
}