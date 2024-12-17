#pragma once
#include "MainWindow.h"
#include "pugixml.hpp"
#include <sstream>

class MainWindow;

class Message
{
public:
	Message();
	Message(std::string _Username, std::string _Message, MainWindow* _MainWindowPtr);
	~Message();

	std::string ConvertXMLtoString();
	

private:

	pugi::xml_document m_XMLDoc;

	std::string m_Message;
	std::string m_Username;
	
	std::string m_Recipricant;
	MainWindow* m_MainWindowPtr;
};