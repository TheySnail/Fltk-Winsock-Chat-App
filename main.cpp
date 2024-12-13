#include <FL/Fl.H>

#include <FL/Fl_Window.H>
#include<FL/Fl_Button.H>

#include "MainWindow.h"
#include "Wsa.h"
#include "ServerSocket.h"
#include <iostream>
#include <vector>
#include <stdexcept>


int main(int argc, char* argv[])
{
	Fl::scheme("gtk+");

	Wsa wsa;

	printf("Initialized Winsock\n");

	std::shared_ptr	<MainWindow> MW = std::make_shared<MainWindow>();


	MW->show(argc, argv);


	return Fl::run();

}