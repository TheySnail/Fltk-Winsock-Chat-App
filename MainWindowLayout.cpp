#include "MainWindowLayout.h"

MainWindowLayout::MainWindowLayout()
	: Fl_Window(640, 480, "PFI Program")//probably should change name
	, m_mainCol(0, 0, 640, 480)
	, m_menuMainCol(0, 0, 640, 480)
	, m_menuBar(0, 0, 640, 20)
	, m_topRow(0, 0, 640, 480)
	, m_midRow(0, 0, 640, 480)
	, m_spacerRow(0, 0, 640, 480)
	, m_bottomRow(0, 0, 640, 480)
	, m_spacer(0, 0, 10, 10)
	, m_spacer2(0, 0, 10, 10)
	, m_spacer3(0, 0, 10, 10)
	, m_CreateServerBttn(0, 0, 0, 0, "Create Server")
	, m_CreateClientBttn(0, 0, 0, 0, "Join as Client")

	,m_ServerMainCol(0,0,640,480)

	, m_IpScreenMainCol(0, 0, 640, 480)
	, m_IpTopRow(0, 0, 640, 480)
	, m_IpInputRow(0, 0, 640, 480)
	, m_IpUsernameInputRow(0, 0, 640, 480)
	, m_IpBttnRow(0, 0, 640, 480)
	, m_IpBottomRow(0, 0, 640, 480)
	, m_IpSpacerRow1(0, 0, 640, 480)
	, m_IpSpacerRow2(0, 0, 640, 480)
	, m_IpInputBox(0, 0, 100, 200, "Enter IP Address")
	, m_UsernameInputBox(0, 0, 100, 200, "Enter Username")
	, m_IpSpacer1(0, 0, 10, 10)
	, m_IpSpacer2(0, 0, 10, 10)
	, m_IpSpacer3(0, 0, 10, 10)
	, m_IpSpacer4(0, 0, 10, 10)
	, m_IpSpacer5(0, 0, 10, 10)
	, m_IpSpacer6(0, 0, 10, 10)
	, m_IpConfirmBttn(0, 0, 0, 0, "Confirm")

	, m_ClientMainCol(0, 0, 640, 480)
	, m_clientTopRow(0,0,640,480)
	, m_ClientBottomRow(0, 0, 640, 480)
	, m_textBuffer(0, 0)
	, m_textDisplay(0, 0, 640, 480)
	, m_MessageInput(0, 0, 100, 200, "")
	, m_MessageSendBttn(0,0,0,0,"Send Message")
	

{

	add_resizable(m_mainCol);//adds main col to window
	m_mainCol.add(m_menuBar);
	m_mainCol.fixed(m_menuBar, 30);//locks menu bar

#pragma region MainMenu 

	//Main Menu Layout


	m_mainCol.add_resizable(m_menuMainCol);//adds main menu col

	//row above the buttons
	m_menuMainCol.add_resizable(m_topRow);



	//row the buttons sit on
	m_menuMainCol.add_resizable(m_midRow);
	
	m_midRow.type(Fl_Flex::ROW);//makes the middle row act as a row not a col
	m_menuMainCol.fixed(m_midRow, 200);

	//buttons
	m_midRow.add_resizable(m_spacer2);

	m_midRow.add_resizable(m_CreateClientBttn);
	m_midRow.fixed(m_CreateClientBttn, 200);

	m_midRow.add_resizable(m_spacer);

	m_midRow.add_resizable(m_CreateServerBttn);
	m_midRow.fixed(m_CreateServerBttn, 200);

	m_midRow.add_resizable(m_spacer3);

	//spacer row to make buttons sit in middle properly
	m_menuMainCol.add_resizable(m_spacerRow);


	//row below buttons
	m_menuMainCol.add_resizable(m_bottomRow);


#pragma endregion

#pragma region Sever Screen
	//server Screen
	m_mainCol.add_resizable(m_ServerMainCol);

#pragma endregion


#pragma region IP input Screen


	m_mainCol.add_resizable(m_IpScreenMainCol);// adds main col for ip screen

	//top row
	m_IpScreenMainCol.add_resizable(m_IpTopRow);
	//m_IpScreenMainCol.fixed(m_IpTopRow, 200);

	//adds row IP input box is on
	m_IpScreenMainCol.add_resizable(m_IpInputRow);
	m_IpInputRow.type(Fl_Flex::ROW);
	m_IpScreenMainCol.fixed(m_IpInputRow, 50);

	m_IpInputRow.add_resizable(m_IpSpacer1);

	m_IpInputRow.add_resizable(m_IpInputBox);
	m_IpInputRow.fixed(m_IpInputBox, 200);

	m_IpInputRow.add_resizable(m_IpSpacer2);

	//spacer row 1
	m_IpScreenMainCol.add_resizable(m_IpSpacerRow1);

	//row username input is on
	m_IpScreenMainCol.add_resizable(m_IpUsernameInputRow);
	m_IpUsernameInputRow.type(Fl_Flex::ROW);
	m_IpScreenMainCol.fixed(m_IpUsernameInputRow, 50);

	m_IpUsernameInputRow.add_resizable(m_IpSpacer3);

	//username input box
	m_IpUsernameInputRow.add_resizable(m_UsernameInputBox);
	m_IpUsernameInputRow.fixed(m_UsernameInputBox, 200);

	m_IpUsernameInputRow.add_resizable(m_IpSpacer4);

	//spacer row 2
	m_IpScreenMainCol.add_resizable(m_IpSpacerRow2);

	//row button is on
	m_IpScreenMainCol.add_resizable(m_IpBttnRow);
	m_IpBttnRow.type(Fl_Flex::ROW);
	m_IpScreenMainCol.fixed(m_IpBttnRow, 50);

	m_IpBttnRow.add_resizable(m_IpSpacer5);
	m_IpBttnRow.add_resizable(m_IpConfirmBttn);
	m_IpBttnRow.fixed(m_IpConfirmBttn, 200);

	m_IpBttnRow.add_resizable(m_IpSpacer6);

	//bottom row
	m_IpScreenMainCol.add_resizable(m_IpBottomRow);
	//m_IpScreenMainCol.fixed(m_IpBottomRow, 200);


#pragma endregion

#pragma region Client screen




	m_mainCol.add_resizable(m_ClientMainCol);

	m_ClientMainCol.add_resizable(m_clientTopRow);

	m_clientTopRow.margin(10, 10);

	m_clientTopRow.add_resizable(m_textDisplay);

	m_ClientMainCol.add_resizable(m_ClientBottomRow);

	m_ClientBottomRow.type(Fl_Flex::ROW);
	m_ClientMainCol.fixed(m_ClientBottomRow, 50);
	m_ClientBottomRow.margin(10, 10);

	m_ClientBottomRow.add_resizable(m_MessageInput);
	m_ClientBottomRow.add_resizable(m_MessageSendBttn);
	m_ClientBottomRow.fixed(m_MessageSendBttn, 100);

#pragma endregion

	this->resize(x(), y(), w()+5, h());
	this->resize(x(),y(),w()-5,h());

}


void MainWindowLayout::ChangeLayout(LayoutType _ScreenState)
{
	switch (_ScreenState)//hides groups of widegets based on what screen should be showing
	{
	case MainMenu:
		{

			m_IpScreenMainCol.hide();
			m_ClientMainCol.hide();
			m_ServerMainCol.hide();
			m_menuMainCol.show();

			m_textDisplay.hide();

			/*m_textDisplay.hide();
			m_MessageInput.hide();
			m_MessageSendBttn.hide();
			m_ClientBottomRow.hide();*/

			//resizes the screen to make sure widgets are showing in correct positions
			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			CurrentLayout = MainMenu;
			break;
		}
	case ClientScreen:
		{
			m_textDisplay.show();

			m_IpScreenMainCol.hide();
			m_menuMainCol.hide();
			m_ServerMainCol.hide();
			m_ClientMainCol.show();
			
			
			//resizes the screen to make sure widgets are showing in correct positions
			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			CurrentLayout = ClientScreen;
			break;
		}
	case ServerScreen:
		{
			m_ClientMainCol.hide();
			m_menuMainCol.hide();
			m_IpScreenMainCol.hide();
			m_ServerMainCol.show();

			m_textDisplay.hide();
			//resizes the screen to make sure widgets are showing in correct positions
			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			CurrentLayout = ServerScreen;
			break;
		}
	case ClientIpScreen:
		{
			
			m_ClientMainCol.hide();
			m_menuMainCol.hide();
			m_ServerMainCol.hide();
			m_IpScreenMainCol.show();

			m_textDisplay.hide();

			//resizes the screen to make sure widgets are showing in correct positions
			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			CurrentLayout = ClientIpScreen;
			break;
		}
	default:
		break;
	}
}

void MainWindowLayout::ChangeTheme(ProgramTheme _Theme)
{
	switch (_Theme)
	{
	case Light:
	{
		m_menuBar.color(fl_rgb_color(255, 255, 255));

		m_CreateClientBttn.color(fl_rgb_color(255, 255, 255));
		m_CreateServerBttn.color(fl_rgb_color(255, 255, 255));
		m_IpConfirmBttn.color(fl_rgb_color(255, 255, 255));
		m_MessageSendBttn.color(fl_rgb_color(255, 255, 255));

		Fl::background(255, 255, 255);
		Fl::foreground(0, 0, 0);
		Fl::background2(255, 255, 255);

		ChangeLayout(CurrentLayout);// forces a redraw on current layout so colours get updated
		break;
	}
		
	case Dark:
	{
		m_menuBar.color(fl_rgb_color(60, 60, 60));

		m_CreateClientBttn.color(fl_rgb_color(60, 60, 60));
		m_CreateServerBttn.color(fl_rgb_color(60, 60, 60));
		m_IpConfirmBttn.color(fl_rgb_color(60, 60, 60));
		m_MessageSendBttn.color(fl_rgb_color(60, 60, 60));

		Fl::background(40, 40, 40);//main background
		Fl::foreground(255, 255, 255); //text
		Fl::background2(80, 80, 80);//other background elements like buttons

		ChangeLayout(CurrentLayout);// forces a redraw on current layout so colours get updated
		break;
	}

	case Bird:
	{
		m_menuBar.color(fl_rgb_color(25, 39, 52));

		m_CreateClientBttn.color(fl_rgb_color(34, 48, 60));
		m_CreateServerBttn.color(fl_rgb_color(34, 48, 60));
		m_IpConfirmBttn.color(fl_rgb_color(34, 48, 60));
		m_MessageSendBttn.color(fl_rgb_color(34, 48, 60));

		Fl::background(30, 41, 52);
		Fl::foreground(255, 255, 255);
		Fl::background2(136, 153, 166);

		ChangeLayout(CurrentLayout);// forces a redraw on current layout so colours get updated
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

