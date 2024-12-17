#pragma once
#ifndef _WINDOW_LAYOUT_
#define _WINDOW_LAYOUT_

#include <FL/Fl.H>

#include <FL/Fl_Window.H>
#include<FL/Fl_Button.H>
#include<FL/Fl_Box.H>

#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Scrollbar.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Text_Buffer.H>
#include <FL/Fl_Text_Display.H>

#include <FL/Fl_Group.H>
#include <FL/Fl_Flex.H>
#include <FL/fl_draw.H>

#include <vector>
#include <iostream>
#include <memory>


enum LayoutType
{
	MainMenu,
	ClientScreen,
	ClientIpScreen,
	ServerScreen,
	ShowReinputUsername,
	HideReinputUsername
};

enum ProgramTheme
{
	Light,
	Dark,
	Bird,
	Blossom,
	Beige,
	Hacker
};

class MainWindowLayout : public Fl_Window
{	
public:
	MainWindowLayout();

	void ChangeLayout(LayoutType _ScreenState);
	void ChangeTheme(ProgramTheme _Theme);

protected:

	Fl_Flex m_MainCol;

	Fl_Menu_Bar m_MenuBar;

	

	//main menu assets
	Fl_Flex m_MenuMainCol;

	Fl_Flex m_MenuTopRow;
	Fl_Flex m_MenuMidRow;
	Fl_Flex m_MenuBottomRow;
	Fl_Flex m_MenuSpacerRow;

	Fl_Box m_MenuSpacer1;
	Fl_Box m_MenuSpacer2;
	Fl_Box m_MenuSpacer3;

	Fl_Button m_CreateServerBttn;
	Fl_Button m_CreateClientBttn;
	

	//server view assets 
	Fl_Flex m_ServerMainCol;
	Fl_Flex m_ServerTopCol;
	Fl_Flex m_ServerBottomRow;

	Fl_Text_Buffer m_ServerBuffer;
	Fl_Text_Display m_ServerDisplay;

	Fl_Input m_ServerMessageInput;
	Fl_Button m_ServerMessageSendBttn;

	//IP input screen
	Fl_Flex m_IpScreenMainCol;
	Fl_Flex m_IpTopRow;
	Fl_Flex m_IpInputRow;
	Fl_Flex m_IpUsernameInputRow;
	Fl_Flex m_IpBttnRow;
	Fl_Flex m_IpBottomRow;
	Fl_Flex m_IpSpacerRow1;
	Fl_Flex m_IpSpacerRow2;

	
	Fl_Box m_IpSpacer1;
	Fl_Box m_IpSpacer2;

	Fl_Box m_IpSpacer3;
	Fl_Box m_IpSpacer4;

	Fl_Box m_IpSpacer5;
	Fl_Box m_IpSpacer6;

	Fl_Input m_IpInputBox;
	Fl_Input m_UsernameInputBox;

	Fl_Button m_IpConfirmBttn;

	
	//client view assets
	
	Fl_Flex m_ClientMainCol;
	Fl_Flex m_ClientTopRow;
	Fl_Flex m_ClientBottomRow;
	Fl_Text_Buffer m_ClientTextBuffer;
	Fl_Text_Display m_ClientTextDisplay;

	Fl_Input m_MessageInput;
	Fl_Button m_MessageSendBttn;

	//username row
	Fl_Flex m_UserNameRow;
	Fl_Input m_UsernameReinputBox;
	Fl_Box m_ReinputSpacer;
	Fl_Button m_UsernameReinputBttn;

	//about 
	Fl_Flex m_AboutRow;
	Fl_Flex m_AboutSpacer1;
	Fl_Flex m_AboutBox;
	Fl_Flex m_AboutSpacer2;

	//server info
	Fl_Flex m_ServerInfoRow;
	Fl_Flex m_ServerInfoSpacer1;
	Fl_Text_Buffer m_ServerInfoBuffer;
	Fl_Text_Display m_ServerInfoDisplay;
	Fl_Flex m_ServerInfoSpacer2;

	LayoutType CurrentLayout;

};


#endif // !_WINDOW_LAYOUT_