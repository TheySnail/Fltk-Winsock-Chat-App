#include "MainWindowLayout.h"

MainWindowLayout::MainWindowLayout()
	: Fl_Window(640, 480, "PFI Program")//probably should change name

	//, m_CreateServerBttn(10, 220, 125, 150, "Create Server")
	//, m_CreateClientBttn(10, 220, 125, 150, "Join as Client")
	, m_MainMenuGroup(nullptr)
	, m_ServerViewGroup(nullptr)
	, m_ClientViewGroup(nullptr)
	, m_IpInputScreenGroup(nullptr)

	, m_mainCol(0, 0, 640, 480)
	, m_menuMainCol(0, 0, 640, 480)
	, m_menuBar(0, 0, 640, 20)
	, m_topRow(0, 0, 640, 480)
	, m_midRow(0, 0, 640, 480)
	, m_bottomRow(0, 0, 640, 480)
	, m_spacer(0, 0, 10, 10)
	, m_spacer2(0, 0, 10, 10)
	, m_spacer3(0, 0, 10, 10)
	, m_CreateServerBttn(0, 0, 0, 0, "Create Server")
	, m_CreateClientBttn(0, 0, 0, 0, "Join as Client")

	, m_IpScreenMainCol(0, 0, 640, 480)
	, m_IpTopRow(0, 0, 640, 480)
	, m_IpMidRow(0, 0, 640, 480)
	, m_IpBottomRow(0, 0, 640, 480)
	, m_IpInputBox(0, 0, 100, 200, "Enter Text")
	, m_IpSpacer(0, 0, 10, 10)
	, m_IpSpacer2(0, 0, 10, 10)
	, m_IpSpacer3(0, 0, 10, 10)
	, m_IpConfirmBttn(0, 0, 0, 0, "Confirm")

	, m_ClientMainCol(0, 0, 640, 480)
	, m_LeftSideBox(0, 0, 10, 10)
	, m_MessageInput(0, 0, 100, 200, "Enter Message")
	, m_MessageSendBttn(0,0,0,0,"Send Message")
	, m_textBuffer(0,0)
	, m_textDisplay(0,0,10,10)

{

	add_resizable(m_mainCol);//adds main col to window
	m_mainCol.add(m_menuBar);
	m_mainCol.fixed(m_menuBar, 30);//locks menu bar

#pragma region MainMenu 

	//Main Menu Layout

	m_MainMenuGroup =  std::make_shared<Fl_Group>(0, 0, 640, 480);

	m_mainCol.add_resizable(m_menuMainCol);//adds main menu col

	//row above the buttons
	m_menuMainCol.add_resizable(m_topRow);
	m_topRow.type(Fl_Flex::ROW);
	m_menuMainCol.fixed(m_topRow, 100);

	//row the buttons sit on
	m_menuMainCol.add_resizable(m_midRow);
	m_menuMainCol.fixed(m_midRow, 200);

	m_midRow.type(Fl_Flex::ROW);//makes the middle row act as a row not a col
	//m_midRow.margin(100);
	
	//buttons
	m_midRow.add_resizable(m_spacer2);

	m_midRow.add_resizable(m_CreateClientBttn);
	m_midRow.fixed(m_CreateClientBttn, 200);

	m_midRow.add_resizable(m_spacer);

	m_midRow.add_resizable(m_CreateServerBttn);
	m_midRow.fixed(m_CreateServerBttn, 200);

	m_midRow.add_resizable(m_spacer3);

	//row below buttons
	m_menuMainCol.add_resizable(m_bottomRow);
	m_menuMainCol.fixed(m_bottomRow, 100);
	m_bottomRow.type(Fl_Flex::ROW);


	m_MainMenuGroup->add_resizable(m_menuMainCol);

	m_MainMenuGroup->end();

#pragma endregion

#pragma region Sever Screen
	//server Screen
	m_ServerViewGroup = std::make_shared<Fl_Group>(0, 0,0,0);

	//m_ServerViewGroup->add_resizable(m_mainCol);

	m_ServerViewGroup->end();

#pragma endregion

#pragma region Client screen

	//client Screen
	m_ClientViewGroup = std::make_shared<Fl_Group>(0, 0, 640, 480);

	m_mainCol.add_resizable(m_ClientMainCol);

	m_ClientMainCol.add_resizable(m_LeftSideBox);

	m_LeftSideBox.add_resizable(m_MessageInput);
	m_LeftSideBox.add_resizable(m_MessageSendBttn);
	m_LeftSideBox.add_resizable(m_textDisplay);

	m_ClientViewGroup->add_resizable(m_ClientMainCol);
	m_ClientViewGroup->end();

#pragma endregion

#pragma region IP input Screen

	m_IpInputScreenGroup = std::make_shared<Fl_Group>(0, 0, 640, 480);

	m_mainCol.add_resizable(m_IpScreenMainCol);// adds main col for ip screen

	m_IpScreenMainCol.add_resizable(m_IpTopRow);//top row
	m_IpScreenMainCol.fixed(m_IpTopRow, 200);

	m_IpScreenMainCol.add_resizable(m_IpMidRow);//adds row input box is on
	m_IpMidRow.type(Fl_Flex::ROW);
	m_IpScreenMainCol.fixed(m_IpMidRow, 50);

	m_IpMidRow.add_resizable(m_IpSpacer);

	m_IpMidRow.add_resizable(m_IpInputBox);
	m_IpMidRow.fixed(m_IpInputBox, 200);

	m_IpMidRow.add_resizable(m_IpSpacer2);

	m_IpMidRow.add_resizable(m_IpConfirmBttn);

	m_IpMidRow.add_resizable(m_IpSpacer3);

	m_IpScreenMainCol.add_resizable(m_IpBottomRow);//bottom row
	m_IpScreenMainCol.fixed(m_IpBottomRow, 200);

	m_IpInputScreenGroup->add_resizable(m_IpScreenMainCol);

	m_IpInputScreenGroup->end();

#pragma endregion



	m_mainCol.add_resizable(*m_MainMenuGroup);
	m_mainCol.add_resizable(*m_ServerViewGroup);
	m_mainCol.add_resizable(*m_ClientViewGroup);
	m_mainCol.add_resizable(*m_IpInputScreenGroup);


	this->resize(x(), y(), w()+5, h());
	this->resize(x(),y(),w()-5,h());

	//m_MainMenuGroup->hide();
}


void MainWindowLayout::ChangeLayout(LayoutType _ScreenState)
{
	switch (_ScreenState)//hides groups of widegets based on what screen should be showing
	{
	case MainMenu:
		{
			m_ClientViewGroup->hide();
			m_ServerViewGroup->hide();
			m_MainMenuGroup->show();
			m_IpInputScreenGroup->hide();
			//resizes the screen to make sure widgets are showing in correct positions
			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			break;
		}
	case ClientScreen:
		{
			m_ClientViewGroup->show();
			m_ServerViewGroup->hide();
			m_MainMenuGroup->hide();
			m_IpInputScreenGroup->hide();
			//resizes the screen to make sure widgets are showing in correct positions
			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			break;
		}
	case ServerScreen:
		{
			m_ClientViewGroup->hide();
			m_ServerViewGroup->show();
			m_MainMenuGroup->hide();
			m_IpInputScreenGroup->hide();
			//resizes the screen to make sure widgets are showing in correct positions
			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			break;
		}
	case ClientIpScreen:
		{
			m_ClientViewGroup->hide();
			m_ServerViewGroup->hide();
			m_MainMenuGroup->hide();
			m_IpInputScreenGroup->show();
			//resizes the screen to make sure widgets are showing in correct positions
			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			break;
		}
	default:
		break;
	}
}



//add_resizable(m_mainCol);
//
//m_mainCol.add_resizable(m_menuBar);
//m_mainCol.add_resizable(m_contentBox);
//m_mainCol.add_resizable(m_midRow);
//
//m_mainCol.fixed(m_menuBar, 30);
//m_mainCol.fixed(m_midRow, 40);
//
///*m_midRow.type(Fl_Flex::ROW);
//m_midRow.margin(5);
//m_midRow.add_resizable(m_CreateClientBttn);
//m_midRow.add_resizable(m_CreateServerBttn);
//m_midRow.fixed(m_CreateClientBttn, 120);
//m_midRow.fixed(m_CreateClientBttn, 120);*/
//
//m_contentBox.color(fl_rgb_color(255, 0, 0));
//m_contentBox.box(FL_DOWN_BOX);
//
//
///*m_CreateClientBttn.position(w() / 2 - m_CreateClientBttn.w() * 1.5 , h() /2 - m_CreateClientBttn.h()/2);
//m_CreateServerBttn.position(w() - m_CreateServerBttn.w() - m_CreateServerBttn.w() - 20, h() / 2 - m_CreateServerBttn.h()/2);*/
//
////m_menuBar.color(fl_rgb_color(140, 140, 140));

