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
	ServerScreen
};

enum ProgramTheme
{
	Light,
	Dark,
	Bird
};

class MainWindowLayout : public Fl_Window
{	
public:
	MainWindowLayout();

	void ChangeLayout(LayoutType _ScreenState);
	void ChangeTheme(ProgramTheme _Theme);

protected:

	Fl_Flex m_mainCol;

	Fl_Menu_Bar m_menuBar;



	//main menu assets
	Fl_Flex m_menuMainCol;

	Fl_Flex m_topRow;
	Fl_Flex m_midRow;
	Fl_Flex m_bottomRow;
	Fl_Flex m_spacerRow;

	Fl_Box m_spacer;
	Fl_Box m_spacer2;
	Fl_Box m_spacer3;

	Fl_Button m_CreateServerBttn;
	Fl_Button m_CreateClientBttn;
	

	//server view assets 
	Fl_Flex m_ServerMainCol;
	

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

	Fl_Text_Buffer m_textBuffer;
	Fl_Text_Display m_textDisplay;

	Fl_Input m_MessageInput;
	Fl_Button m_MessageSendBttn;

	LayoutType CurrentLayout;
	
};


#endif // !_WINDOW_LAYOUT_