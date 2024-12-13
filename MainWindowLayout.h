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

class MainWindowLayout : public Fl_Window
{	
public:
	MainWindowLayout();

	void ChangeLayout(LayoutType _ScreenState);

protected:

	Fl_Flex m_mainCol;

	Fl_Menu_Bar m_menuBar;

	std::shared_ptr<Fl_Group> m_MainMenuGroup;
	std::shared_ptr<Fl_Group> m_ServerViewGroup;
	std::shared_ptr<Fl_Group> m_ClientViewGroup;
	std::shared_ptr<Fl_Group> m_IpInputScreenGroup;

	//main menu assets
	Fl_Flex m_menuMainCol;

	Fl_Flex m_topRow;
	Fl_Flex m_midRow;
	Fl_Flex m_bottomRow;

	Fl_Box m_spacer;
	Fl_Box m_spacer2;
	Fl_Box m_spacer3;

	Fl_Button m_CreateServerBttn;
	Fl_Button m_CreateClientBttn;
	

	//server view assets 
	
	//client view assets
	Fl_Flex m_ClientMainCol;
	
	Fl_Flex m_LeftSideBox;

	Fl_Input m_MessageInput;
	Fl_Button m_MessageSendBttn;

	Fl_Text_Buffer m_textBuffer;
	Fl_Text_Display m_textDisplay;

	//IP input screen

	Fl_Flex m_IpScreenMainCol;
	Fl_Flex m_IpTopRow;
	Fl_Flex m_IpMidRow;
	Fl_Flex m_IpBottomRow;

	Fl_Input m_IpInputBox;
	Fl_Box m_IpSpacer;
	Fl_Box m_IpSpacer2;
	Fl_Box m_IpSpacer3;


	Fl_Button m_IpConfirmBttn;


	/*Fl_Text_Buffer m_IpBuff;
	Fl_Text_Display m_IpDisplay;*/
	
	
	
};


#endif // !_WINDOW_LAYOUT_