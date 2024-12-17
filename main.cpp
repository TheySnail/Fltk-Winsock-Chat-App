#include <FL/Fl.H>

#include <FL/Fl_Window.H>
#include<FL/Fl_Button.H>

#include "MainWindow.h"
#include "Wsa.h"
#include "ServerSocket.h"
#include <iostream>
#include <vector>
#include <stdexcept>
#include <windows.h>


int main(int argc, char* argv[])
{
	//hides the console 
	FreeConsole();

	Fl::scheme("gtk+");

	Wsa wsa;

	printf("Initialized Winsock\n");

	std::shared_ptr	<MainWindow> MW = std::make_shared<MainWindow>();

	int  x,y,w, h;

	Fl::screen_xywh(x, y, w, h);//gets x y w h of monitor dont need the x and y but needed to store them

	MW->size_range(400, 400, w, h);
	//sets the min and max size the window can be so users cant make widgets overlap weirdly
	//and it lets them full screen the application no matter the size of their monitor but not more

	MW->show(argc, argv);


	return Fl::run();

}