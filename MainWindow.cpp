#include "MainWindow.h"
#include <stdexcept>

#include "Server.h"
#include <FL/Fl_ask.h>


MainWindow::MainWindow()
	: m_Server(nullptr)
	, m_Client(nullptr)
	, m_ServerActive(false)

{	


	m_CreateServerBttn.callback(CreateServer, this);
	m_CreateClientBttn.callback(StaticCreateClient, this);
	m_IpConfirmBttn.callback(ConfirmIp, this);
	m_MessageSendBttn.callback(StaticSendUserMessage, this);

	m_menuBar.add("&File/&Open", "^o", NULL);
	m_menuBar.add("&File/&Save", "^s", NULL,0, FL_MENU_DIVIDER);
	m_menuBar.add("&File/&Exit", "^e", CreateServer, this);

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

void MainWindow::ConfirmIp(Fl_Widget* _widget, void* _userData)
{
	MainWindow* mw = (MainWindow*)_userData;
	try
	{
		std::string buffer;

		buffer = mw->m_IpInputBox.value();

		std::cout << std::endl << "buffer is " << buffer << std::endl;

		mw->m_IpInputBox.value("");

		mw->m_Client->InputIpAddr(buffer);

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
	m_Client->ClientSend(buffer);
}

void MainWindow::AddToDisplay(std::string _buffer)
{
	m_textBuffer.append(_buffer.c_str());
	m_textBuffer.append("\n");
	m_textDisplay.buffer(m_textBuffer);
}


//void MainWindow::on_tick()
//{
//	//printf("tick");
//	std::shared_ptr<ClientSocket> client = server.accept();
//
//	if (client)
//	{
//		printf("CLinet Connect!\n");
//		clients.push_back(client);
//	}
//
//
//	for (size_t ci = 0; ci < clients.size(); ++ci)
//	{
//		std::string message;
//
//		while (clients.at(ci)->receive(message))
//		{
//			printf("Message recived: %s\n", message.c_str());
//		}
//
//		if (clients.at(ci)->m_closed)
//		{
//			printf("Client Disconnected\n");
//			clients.erase(clients.begin() + ci);
//			ci--;
//		}
//	}
//}


//MainWindow::MainWindow() 
//	: Fl_Window(640, 480, "Main Window")
//	, m_close(10, 10, 120, 30, "CLose")
//	, m_imageBox(10,100,100,100, "Hello")
//	, m_img("cat.png")
//
//{
//	m_close.callback(on_cLick, this);
//
//	m_imageBox.box(FL_DOWN_BOX);
//	m_imageBox.color(fl_rgb_color(100, 100, 10));
//
//	if (m_img.fail())
//	{
//		throw std::runtime_error("Failed");
//	}
//	
//	m_imageBox.image(m_img);
//	icon(&m_img);
//}
//
//void MainWindow::on_cLick(Fl_Widget* _widget, void* _userData)
//{
//	Fl_Window* win = (Fl_Window*)_userData;
//	win->hide();
//}