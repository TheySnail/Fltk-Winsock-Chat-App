#pragma once
#include "MainWindow.h"
#include "pugixml.hpp"
#include <sstream>


class Message
{
public:
	Message();
	Message(std::string _Username, std::string _Message);
	~Message();

	std::string ConvertXMLtoString();


private:

	pugi::xml_document m_XMLDoc;

	std::string m_message;
	std::string m_username;
	
	std::string m_recipricant;

};