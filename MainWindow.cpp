#include "MainWindow.h"
#include <stdexcept>

#include "Server.h"
#include <FL/Fl_ask.h>

#include "message.h"

//add change username
//add server info
//add client about

MainWindow::MainWindow()
	: m_Server(nullptr)
	, m_Client(nullptr)
	, m_ServerActive(false)
	, m_Username("Anonymous")
	, m_HasAdmin(false)
	, m_AboutBoxShown(false)
	, m_ServerInfoBoxShown(false)
	, m_ClientConnected(false)

{	


	m_CreateServerBttn.callback(StaticCreateServer, this);
	m_CreateClientBttn.callback(StaticCreateClient, this);

	m_UsernameReinputBttn.callback(GetNewUsername, this);
	m_UsernameReinputBox.callback(GetNewUsername, this);
	m_UsernameReinputBox.when(FL_WHEN_ENTER_KEY);

	m_IpConfirmBttn.callback(StaticConfirmIp, this);
	m_IpInputBox.callback(StaticConfirmIp, this);
	m_IpInputBox.when(FL_WHEN_ENTER_KEY);

	//call back functions for client and server screens they use the same function but with different widgets
	m_MessageSendBttn.callback(StaticSendUserMessage, this);
	m_MessageInput.callback(StaticSendUserMessage, this);
	m_MessageInput.when(FL_WHEN_ENTER_KEY);

	m_ServerMessageSendBttn.callback(StaticSendUserMessage, this);
	m_ServerMessageInput.callback(StaticSendUserMessage, this);
	m_ServerMessageInput.when(FL_WHEN_ENTER_KEY);

	m_MenuBar.add("&Return/&Return To Menu", "^b", StaticReturnToMainMenu, this);
	m_MenuBar.add("&Return/&Exit", "^e", Close, this);
	m_MenuBar.add("&Theme/&Light", NULL, ChangeToLight, this);
	m_MenuBar.add("&Theme/&Dark", NULL, ChangeToDark, this);
	m_MenuBar.add("&Theme/&Bird", NULL, ChangeToBird, this);
	m_MenuBar.add("&Theme/&Blossom", NULL, ChangeToBlossom, this);
	m_MenuBar.add("&Theme/&Beige", NULL, ChangeToBeige, this);
	m_MenuBar.add("&Theme/&Hacker", NULL, ChangeToHacker, this);
	m_MenuBar.add("&About/&Show About Box", NULL, ShowAboutInfo, this);
	m_MenuBar.add("&Server/&Request Server Info", NULL, RequestSeverData, this);
	m_MenuBar.add("&User Name/&Change User Name", "", ShowChangeUsernameBox, this);
	
	ChangeLayout(MainMenu);
}
//Ive used regions to organise functions so this file is more readable
#pragma region Callback Functions

#pragma region Buttons
void MainWindow::StaticCreateServer(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;

	mw->CreateServer();

}

void MainWindow::CreateServer()
{
	if (this->m_ServerActive == false)
	{
		this->m_Server = std::make_shared<Server>();

		m_Client = std::make_shared<Client>(this);
		m_HasAdmin = true;
		this->m_Username = "Host";
		m_Client->InputIpAddr("127.0.0.1");


		std::cout << "server created" << std::endl;

		this->m_ServerActive = true;

		this->ChangeLayout(ServerScreen);
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

		std::string NewUserName;

		if (mw->m_UsernameInputBox.value() != "")//if they entered a username run username validation
		{
			NewUserName = mw->m_UsernameInputBox.value();

			bool UsernameValid = true;

			for (char c : NewUserName)
			{
				if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') || NewUserName.length() > 12)//if username is only chars and under 12 characters makes handling the data easier 
				{
					std::cout << "invalid username detected";
					mw->m_UsernameInputBox.value("");

					fl_alert("Usernames can only contain lowercase and uppercase letters and under 12 characters long");
					UsernameValid = false;
					break;//break here as theres no point to keep iterating 
				}
			}

			if (UsernameValid)
			{
				mw->m_Username = NewUserName;
				mw->m_Client->InputIpAddr(IpBuffer);
			}
		}
		else
		{
			mw->m_Client->InputIpAddr(IpBuffer);
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
	try
	{
		if (this->m_Client->GetClientSocketClosed() == false)
//use a getter on the client to get the client socket closed status if it is closed the client socket is not longer connected to a server and sending a message will crash the client
		{
			std::string buffer;
			if (this->m_HasAdmin)
			{
				buffer = m_ServerMessageInput.value();
			}
			else
			{
				buffer = m_MessageInput.value();
			}


			buffer = buffer + "¶";

			std::shared_ptr <Message>m_MessagePtr;

			if (this->m_HasAdmin)
			{
				m_MessagePtr = std::make_shared<Message>("(Host) " + m_Username, buffer, this);
				//so if the host starts messaging people can see that its the host
			}
			else
			{
				m_MessagePtr = std::make_shared<Message>(m_Username, buffer, this);
			}

			m_Client->ClientSend(m_MessagePtr->ConvertXMLtoString());//sends the converted xml doc as a string

			m_MessageInput.value("");
			m_ServerMessageInput.value("");
		}
		
		else
		{
			fl_alert("Server shutdown or Client Disconnected");
			ReturnToMainMenu();
		}

	}
	catch (std::exception& _e)
	{
		std::string msg = _e.what();
		fl_alert(msg.c_str());
	}
	
}
#pragma endregion

#pragma region Themes
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

void MainWindow::ChangeToBlossom(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	mw->ChangeTheme(Blossom);
}

void MainWindow::ChangeToBeige(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	mw->ChangeTheme(Beige);
}

void MainWindow::ChangeToHacker(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	mw->ChangeTheme(Hacker);
}

#pragma endregion

#pragma region MenuBar 
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
	//sets the buffer to nothing so if client or server leaves room and joins a different one/ rejoins they wont see the old text
	m_ServerBuffer.text("");
	m_ClientTextBuffer.text("");

	//set the points to the client and server to null destroying them
	this->m_Server = nullptr;
	this->m_Client = nullptr;

	this->m_ServerActive = false; //make it so user can create new server if they want
	this->m_HasAdmin = false;
	this->m_ClientConnected = false;

	this->ChangeLayout(MainMenu);// go back to main menu screen

}
#pragma endregion

#pragma endregion

#pragma region Handling Incoming Data and Displaying It Functions

void MainWindow::AddToDisplay(std::string _buffer)
{
	if (_buffer.at(0) == '©')//this char means that the buffer is the server info and doesnt need to be formatted
	{
		_buffer.erase(0, 1);//erase identifier char
		m_ServerInfoBuffer.append(_buffer.c_str());
		m_ServerInfoDisplay.buffer(m_ServerInfoBuffer);
	}
	else//will be a message from user
	{
		if (m_HasAdmin)//if the "client" is the admin client use the display in server window and server buffer
		{
			m_ServerBuffer.append((HandleIncomingXML(_buffer)).c_str());
			m_ServerDisplay.buffer(m_ServerBuffer);
		}
		else
		{
			//passes in the handled incoming xml data as a c string so it can be displayed in text display
			m_ClientTextBuffer.append((HandleIncomingXML(_buffer)).c_str());
			m_ClientTextDisplay.buffer(m_ClientTextBuffer);
		}
	}

}

std::string MainWindow::HandleIncomingXML(std::string _IncomingXML)
{
	_IncomingXML = Rot13(_IncomingXML);//decrypt

	pugi::xml_document tempdoc;

	tempdoc.load_string(_IncomingXML.c_str());//pareses the incoming string back into usable xml

	pugi::xml_node UserData = tempdoc.child("UserData");//creates the root node of incoming xml so i can access it here

	std::string username = UserData.child("Info").child("Username").attribute("Username").value();

	std::string message = UserData.child("UserMessage").child("Message").attribute("Message").value();

	std::string Everyone = "Everyone";//needs to be string so i can compare value of Reciprocant

	std::string TargetChars("<?xml");
	std::string First4Chars;

	for (int i = 0; i <= 4; i++)
	{
		First4Chars = First4Chars + _IncomingXML[i];
	}

	if (First4Chars == TargetChars)//checks to see if the first chars are <?xml if they are the data is starting to be sent;
	{
		//if targeted to this specific user will show for targeted user AND user who sent it so they can see whisper history or show to admin
		if (((UserData.child("Info").child("Reciprocant").attribute("Reciprocant").value() == getUsername()) || (UserData.child("Info").child("Username").attribute("Username").value() == getUsername() || m_HasAdmin) && UserData.child("Info").child("Reciprocant").attribute("Reciprocant").value() != Everyone))
		{
			message.pop_back();//gets rid of null char at end
			std::string completeMessage = username + " whispered to " + UserData.child("Info").child("Reciprocant").attribute("Reciprocant").value() + ": " + message + "\n";
			//displays as
			// user 1 Whispered to user 2 : Message
			return completeMessage;
		}

		//if tartgeted to everyone
		else if (UserData.child("Info").child("Reciprocant").attribute("Reciprocant").value() == Everyone)
		{
			message.pop_back();//gets rid of null char at end
			std::string completeMessage = username + ": " + message + "\n";
			return completeMessage;
		}

		//if targeted to a user which is not this one
		else
		{
			return "";
		}
	}
	else//if message overran
	{
		std::string rtnString;

		for (int i = 0; i <= _IncomingXML.size(); i++)
		{
			if ((_IncomingXML[i] != '¶'))//keep running 
			{
				rtnString = rtnString + _IncomingXML[i];
			}

			//if (i == 128)//if the message being sent if very long add a new line so it is easier to read
			//{
			//	rtnString = rtnString + "\n";
			//}

			else
			{
				rtnString = rtnString + "\n";
				break;
			}
		}
		return rtnString;
	}


}

#pragma endregion

#pragma region Changing Username Functions
void MainWindow::ShowChangeUsernameBox(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	if (mw->CurrentLayout != MainMenu)
	{
		mw->ChangeLayout(ShowReinputUsername);
	}
}

void MainWindow::GetNewUsername(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;

	std::string NewUserName;

	NewUserName = mw->m_UsernameReinputBox.value();

	bool UsernameValid = true;

	for (char c : NewUserName)
	{
		if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z') || NewUserName.length() > 12)//if username is only chars and under 12 characters makes handling the data easier 
		{
			std::cout << "invalid username detected";
			mw->m_UsernameReinputBox.value("");

			fl_alert("Usernames can only contain lowercase and uppercase letters and under 12 characters long");
			UsernameValid = false;
			break;//break here as theres no point to keep iterating 
		}
	}

	if (UsernameValid)
	{
		std::cout << "username fine";
		mw->m_UsernameReinputBox.value("");

		std::string OldUserName;
		OldUserName = mw->m_Username;//store old username so it can be displayed on the change message

		mw->m_Username = NewUserName;

		mw->ChangeLayout(HideReinputUsername);

		mw->m_Client->ClientSend(mw->Rot13(OldUserName + " changed their name to " + mw->m_Username + "\n"));
		//displays their old username and new username and encrypts it (has to be encrypted as it expects a encrypted message)
	}
}

#pragma endregion

#pragma region Requesting Server Info Functions
void MainWindow::ShowAboutInfo(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;

	if (mw->m_AboutBoxShown == false)
	{
		mw->m_AboutRow.show();
		mw->m_AboutBoxShown = true;
		mw->ResizeWindow();
	}
	else
	{
		mw->m_AboutRow.hide();
		mw->m_AboutBoxShown = false;
		mw->ResizeWindow();
	}
}

void MainWindow::RequestSeverData(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;

	if (mw->m_ClientConnected && mw->m_ServerInfoBoxShown == false)//if they havent requested server info and they are connected
	{
		mw->m_Client->RequestServerInfo();//sends special char to server so it knows it needs to send server data back to this client
		mw->m_ServerInfoRow.show();
		mw->ResizeWindow();
		mw->m_ServerInfoBoxShown = true;
	}

	else if (mw->m_ClientConnected && mw->m_ServerInfoBoxShown == true)//if they have requested
	{
		mw->m_ServerInfoBuffer.text("");

		mw->m_ServerInfoRow.hide();
		mw->ResizeWindow();
		mw->m_ServerInfoBoxShown = false;
	}

	else
	{
		fl_alert("You need to be connected to a server to request its data!");
	}
}

#pragma endregion

#pragma region Getters and Setters
void MainWindow::SetClientConnected(bool _Status)
{
	m_ClientConnected = _Status;
}

std::string MainWindow::getUsername()
{
	return m_Username;
}
#pragma endregion

void MainWindow::ResizeWindow()
{
	this->resize(x(), y(), w() + 5, h());
	this->resize(x(), y(), w() - 5, h());
}

std::string MainWindow::Rot13(std::string _message)
{
	std::string EncrytedString;

	for (char c : _message)
	{
		if (c >= 'a' && c <= 'z')
		{
			EncrytedString += (c - 'a' + 13) % 26 + 'a';//works out the correct value for the alphabet (1-26) then adds a back to it to make it into ascii
		}

		else if (c >= 'A' && c <= 'Z')
		{
			EncrytedString += (c - 'A' + 13) % 26 + 'A';//same but caps
		}

		else
		{
			EncrytedString += c;
		}
	}

	return EncrytedString;
}