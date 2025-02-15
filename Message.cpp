#include "Message.h"

Message::Message()
{

}

Message::Message(std::string _Username, std::string _Message, MainWindow* _MainWindowPtr):
	m_Username(_Username)
	, m_Message(_Message)

{
	m_MainWindowPtr = _MainWindowPtr;
	//creating xml doc
	pugi::xml_node UserData = m_XMLDoc.append_child("UserData");
	pugi::xml_node Info = UserData.append_child("Info");
	pugi::xml_node Username = Info.append_child("Username");
	pugi::xml_node Reciprocant = Info.append_child("Reciprocant");
	pugi::xml_node UserMessage = UserData.append_child("UserMessage");
	pugi::xml_node Message = UserMessage.append_child("Message");


	Username.append_attribute("Username").set_value(m_Username.c_str());
	

	// if the first character is a / then someone is trying to private message
	if (_Message.at(0) == '/')
	{
		std::string TargetUser;

		std::cout << "command detected";
		for (size_t i = 1; i < _Message.size(); i++)//will cycle from second char until it hits a space to get username
		{
			if (_Message.at(i) == ' ')//go until there is  a space (no spaces in usernames allowed)
			{
				m_Message.erase(0, 1);
				break;
			}
			TargetUser += _Message.at(i);

			m_Message.erase(0,1);//erases first char of message every time to get rid of the /username command in message

			//std::cout << _Message.at(i);
		}

		std::cout << std::endl << TargetUser << std::endl;

		Reciprocant.append_attribute("Reciprocant").set_value(TargetUser.c_str());
		Message.append_attribute("Message").set_value(m_Message.c_str());
	}

	else
	{
		Message.append_attribute("Message").set_value(m_Message.c_str());
		Reciprocant.append_attribute("Reciprocant").set_value("Everyone");
	}
	
}

Message::~Message()
{
	std::cout << "deleting message object ";
}

std::string Message::ConvertXMLtoString()
{
	std::stringstream ss;
	m_XMLDoc.save(ss);
	std::string XMLString = ss.str();

	XMLString = m_MainWindowPtr->Rot13(XMLString);

	return XMLString;
}



