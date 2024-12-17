#include "MainWindowLayout.h"

MainWindowLayout::MainWindowLayout()
	: Fl_Window(640, 480, "Chat App")

	, m_MainCol(0, 0, 640, 480)

	, m_MenuMainCol(0, 0, 640, 480)
	, m_MenuBar(0, 0, 640, 20)
	, m_MenuTopRow(0, 0, 640, 480)
	, m_MenuMidRow(0, 0, 640, 480)
	, m_MenuSpacerRow(0, 0, 640, 480)
	, m_MenuBottomRow(0, 0, 640, 480)
	, m_MenuSpacer1(0, 0, 10, 10)
	, m_MenuSpacer2(0, 0, 10, 10)
	, m_MenuSpacer3(0, 0, 10, 10)
	, m_CreateServerBttn(0, 0, 0, 0, "Create Server")
	, m_CreateClientBttn(0, 0, 0, 0, "Join as Client")

	, m_ServerMainCol(0, 0, 640, 480)
	, m_ServerTopCol(0, 0, 640, 480)
	, m_ServerBottomRow(0, 0, 640, 480)
	, m_ServerBuffer(0, 0)
	, m_ServerDisplay(0, 0, 640, 480)
	, m_ServerMessageInput(0, 0, 100, 200, "")
	, m_ServerMessageSendBttn(0, 0, 0, 0, "Send Message")

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
	, m_ClientTopRow(0, 0, 640, 480)
	, m_ClientBottomRow(0, 0, 640, 480)
	, m_ClientTextBuffer(0, 0)
	, m_ClientTextDisplay(0, 0, 640, 480)
	, m_MessageInput(0, 0, 100, 200, "")
	, m_MessageSendBttn(0, 0, 0, 0, "Send Message")

	, m_UserNameRow(0, 0, 640, 480)
	, m_UsernameReinputBox(0, 0, 100, 200)
	, m_UsernameReinputBttn(0, 0, 10, 10, "Confirm")
	, m_ReinputSpacer(0, 0, 0, 0)

	, m_AboutRow(0, 0, 640, 480)
	, m_AboutSpacer1(0, 0, 640, 480)
	, m_AboutBox(0, 0, 0, 0)
	, m_AboutSpacer2(0, 0, 640, 480)

	, m_ServerInfoRow(0, 0, 640, 480)
	, m_ServerInfoSpacer1(0, 0, 640, 480)
	, m_ServerInfoBuffer(0, 0)
	, m_ServerInfoDisplay(0, 0, 640, 480)
	, m_ServerInfoSpacer2(0,0,640,480)

	,CurrentLayout(MainMenu)
	

{
	
	add_resizable(m_MainCol);//adds main col to window
	m_MainCol.add(m_MenuBar);
	m_MainCol.fixed(m_MenuBar, 30);//locks menu bar

#pragma region Username Reinput
	//username reinput row
	m_MainCol.add_resizable(m_UserNameRow);
	m_UserNameRow.type(Fl_Flex::ROW);
	m_MainCol.fixed(m_UserNameRow, 50);
	m_UserNameRow.margin(10, 10);

	m_UserNameRow.add_resizable(m_UsernameReinputBox);
	m_UserNameRow.add_resizable(m_ReinputSpacer);
	m_UserNameRow.fixed(m_ReinputSpacer, 10);
	m_UserNameRow.add_resizable(m_UsernameReinputBttn);
	m_UserNameRow.fixed(m_UsernameReinputBttn, 100);

	m_UserNameRow.hide();
#pragma endregion

#pragma region Client About
	m_MainCol.add_resizable(m_AboutRow);
	m_MainCol.fixed(m_AboutRow, 230);
	m_AboutRow.margin(10, 10);
	m_AboutRow.type(Fl_Flex::ROW);

	m_AboutRow.add_resizable(m_AboutSpacer1);

	m_AboutBox.box(FL_UP_BOX);  
	m_AboutBox.label
	(
		"Welcome To My Chat App! \n*******************************\n This chat app lets you host your own chat room  \n or join others. \n Use the buttons bellow to join or host. \n When Joining a room you will be asked to enter a user name,\n this can be changed once in a room by the menu bar.\n You can also change the theme by the menu bar.\n When in a room you can whisper to other users \nby using the /username command (/bob .....)\n Hosts can see all whispers as a form of admin. "
	);              
	
	m_AboutBox.labelsize(16);
	m_AboutBox.align(FL_ALIGN_CENTER);

	m_AboutRow.add_resizable(m_AboutBox);
	m_AboutRow.fixed(m_AboutBox, 450);

	m_AboutRow.add_resizable(m_AboutSpacer2);

	m_AboutRow.hide();
#pragma endregion

#pragma region Server Info
	m_MainCol.add_resizable(m_ServerInfoRow);

	m_ServerInfoRow.type(Fl_Flex::ROW);
	m_MainCol.fixed(m_ServerInfoRow, 75);
	m_ServerInfoRow.margin(10, 10);

	m_ServerInfoRow.add_resizable(m_ServerInfoSpacer1);

	m_ServerInfoRow.add_resizable(m_ServerInfoDisplay);

	m_ServerInfoRow.add_resizable(m_ServerInfoSpacer2);

	m_ServerInfoRow.hide();//hide so it wont be there at start of program
#pragma endregion


#pragma region MainMenu 

	//Main Menu Layout


	m_MainCol.add_resizable(m_MenuMainCol);//adds main menu col

	//row above the buttons
	m_MenuMainCol.add_resizable(m_MenuTopRow);



	//row the buttons sit on
	m_MenuMainCol.add_resizable(m_MenuMidRow);
	
	m_MenuMidRow.type(Fl_Flex::ROW);//makes the middle row act as a row not a col
	m_MenuMainCol.fixed(m_MenuMidRow, 200);

	//buttons
	m_MenuMidRow.add_resizable(m_MenuSpacer2);

	m_MenuMidRow.add_resizable(m_CreateClientBttn);
	m_MenuMidRow.fixed(m_CreateClientBttn, 200);

	m_MenuMidRow.add_resizable(m_MenuSpacer1);

	m_MenuMidRow.add_resizable(m_CreateServerBttn);
	m_MenuMidRow.fixed(m_CreateServerBttn, 200);

	m_MenuMidRow.add_resizable(m_MenuSpacer3);

	//spacer row to make buttons sit in middle properly
	m_MenuMainCol.add_resizable(m_MenuSpacerRow);


	//row below buttons
	m_MenuMainCol.add_resizable(m_MenuBottomRow);


#pragma endregion

#pragma region Sever Screen
	//server Screen
	m_MainCol.add_resizable(m_ServerMainCol);
	m_ServerMainCol.add_resizable(m_ServerTopCol);

	m_ServerTopCol.margin(10, 10);

	m_ServerTopCol.add_resizable(m_ServerDisplay);

	m_ServerMainCol.add_resizable(m_ServerBottomRow);
	m_ServerBottomRow.type(Fl_Flex::ROW);

	m_ServerMainCol.fixed(m_ServerBottomRow, 50);
	m_ServerBottomRow.margin(10, 10);

	m_ServerBottomRow.add_resizable(m_ServerMessageInput);
	m_ServerBottomRow.add_resizable(m_ServerMessageSendBttn);
	m_ServerBottomRow.fixed(m_ServerMessageSendBttn, 100);

#pragma endregion


#pragma region IP input Screen


	m_MainCol.add_resizable(m_IpScreenMainCol);// adds main col for ip screen

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

	m_MainCol.add_resizable(m_ClientMainCol);

	m_ClientMainCol.add_resizable(m_ClientTopRow);

	m_ClientTopRow.margin(10, 10);

	m_ClientTopRow.add_resizable(m_ClientTextDisplay);

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
			m_MenuMainCol.show();

			m_ClientTextDisplay.hide();

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
			m_ClientTextDisplay.show();

			m_IpScreenMainCol.hide();
			m_MenuMainCol.hide();
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
			m_MenuMainCol.hide();
			m_IpScreenMainCol.hide();
			m_ServerMainCol.show();

			m_ClientTextDisplay.hide();
			//resizes the screen to make sure widgets are showing in correct positions
			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			CurrentLayout = ServerScreen;
			break;
		}
	case ClientIpScreen:
		{
			m_ClientMainCol.hide();
			m_MenuMainCol.hide();
			m_ServerMainCol.hide();
			m_IpScreenMainCol.show();

			m_ClientTextDisplay.hide();

			//resizes the screen to make sure widgets are showing in correct positions
			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			CurrentLayout = ClientIpScreen;
			break;
		}
	case ShowReinputUsername:
		{
			m_UserNameRow.show();

			this->resize(x(), y(), w() + 5, h());
			this->resize(x(), y(), w() - 5, h());
			break;
		}
	case HideReinputUsername:
	{
		m_UserNameRow.hide();

		this->resize(x(), y(), w() + 5, h());
		this->resize(x(), y(), w() - 5, h());
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
		m_MenuBar.color(fl_rgb_color(255, 255, 255));

		m_CreateClientBttn.color(fl_rgb_color(255, 255, 255));
		m_CreateServerBttn.color(fl_rgb_color(255, 255, 255));
		m_IpConfirmBttn.color(fl_rgb_color(255, 255, 255));
		m_MessageSendBttn.color(fl_rgb_color(255, 255, 255));

		m_AboutBox.color(fl_rgb_color(255, 255, 255));

		Fl::background(255, 255, 255);
		Fl::foreground(0, 0, 0);
		Fl::background2(255, 255, 255);

		ChangeLayout(CurrentLayout);// forces a redraw on current layout so colours get updated
		break;
	}
		
	case Dark:
	{
		m_MenuBar.color(fl_rgb_color(60, 60, 60));

		m_CreateClientBttn.color(fl_rgb_color(60, 60, 60));
		m_CreateServerBttn.color(fl_rgb_color(60, 60, 60));
		m_IpConfirmBttn.color(fl_rgb_color(60, 60, 60));
		m_MessageSendBttn.color(fl_rgb_color(60, 60, 60));
		m_AboutBox.color(fl_rgb_color(60, 60, 60));

		Fl::background(40, 40, 40);//main background
		Fl::foreground(255, 255, 255); //text
		Fl::background2(80, 80, 80);//other background elements like buttons

		ChangeLayout(CurrentLayout);// forces a redraw on current layout so colours get updated
		break;
	}

	case Bird:
	{
		m_MenuBar.color(fl_rgb_color(25, 39, 52));

		m_CreateClientBttn.color(fl_rgb_color(34, 48, 60));
		m_CreateServerBttn.color(fl_rgb_color(34, 48, 60));
		m_IpConfirmBttn.color(fl_rgb_color(34, 48, 60));
		m_MessageSendBttn.color(fl_rgb_color(34, 48, 60));

		m_AboutBox.color(fl_rgb_color(34, 48, 60));

		Fl::background(30, 41, 52);
		Fl::foreground(255, 255, 255);
		Fl::background2(136, 153, 166);

		ChangeLayout(CurrentLayout);// forces a redraw on current layout so colours get updated
		break;
	}
	case Blossom:
	{
		m_MenuBar.color(fl_rgb_color(255, 179, 198));

		m_CreateClientBttn.color(fl_rgb_color(255, 194, 209));
		m_CreateServerBttn.color(fl_rgb_color(255, 194, 209));
		m_IpConfirmBttn.color(fl_rgb_color(255, 194, 209));
		m_MessageSendBttn.color(fl_rgb_color(255, 194, 209));

		m_AboutBox.color(fl_rgb_color(255, 194, 209));
		

		Fl::background(251, 111, 146);
		Fl::foreground(0, 0, 0);
		Fl::background2(255, 143, 171);

		ChangeLayout(CurrentLayout);// forces a redraw on current layout so colours get updated
		break;
	}
	case Beige:
	{
		m_MenuBar.color(fl_rgb_color(228, 213, 183));

		m_CreateClientBttn.color(fl_rgb_color(255, 240, 219));
		m_CreateServerBttn.color(fl_rgb_color(255, 240, 219));
		m_IpConfirmBttn.color(fl_rgb_color(255, 240, 219));
		m_MessageSendBttn.color(fl_rgb_color(255, 240, 219));

		m_AboutBox.color(fl_rgb_color(255, 240, 219));


		Fl::background(217, 185, 155);
		Fl::foreground(0, 0, 0);
		Fl::background2(238, 217, 196);

		ChangeLayout(CurrentLayout);// forces a redraw on current layout so colours get updated
		break;
	}
	case Hacker:
	{
		m_MenuBar.color(fl_rgb_color(25, 25, 25));

		m_CreateClientBttn.color(fl_rgb_color(40, 40, 40));
		m_CreateServerBttn.color(fl_rgb_color(40, 40, 40));
		m_IpConfirmBttn.color(fl_rgb_color(40, 40, 40));
		m_MessageSendBttn.color(fl_rgb_color(40, 40, 40));

		m_AboutBox.color(fl_rgb_color(40, 40, 40));


		Fl::background(20, 20, 20);
		Fl::foreground(50, 255, 50);
		Fl::background2(30, 30, 30);

		ChangeLayout(CurrentLayout);// forces a redraw on current layout so colours get updated
		break;
	}
	default:
		break;
	}
}
