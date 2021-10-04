#include "ConsoleController.h"
#include "FileReader.h"

#include <string>
#include <iostream>
#include <algorithm>



using namespace ConsoleController_N;
using namespace FileReader;

Reader fileReader;

std::string ConsoleController_N::ConsoleCtrl::Commands(std::string command)
{
	std::string ans = "";
	transform(command.begin(), command.end(), command.begin(), std::tolower); //ensures that all input is lowercase to prevent errors from llooking for a lowercase word that is in upercase.
	fileReader.SplitString(command);
	//std::cout << command;
	if (command == "fps") {
		std::cout << "Current Frames Per Second is: " << GetFPS() << std::endl;
	}
	else if (command == "triangles") {

	}
	else if (command == "load") { //needs to check 1st word and store the 2nd word

	}	
	else if (command == "spawn") {  //needs to check 1st word and store the 2nd word

	}
	else {
		std::cout << "Unrecognised Command" << std::endl;
		ans = "CONSOLE";
	}
	return ans;
}



ConsoleCtrl::ConsoleCtrl::ConsoleCtrl() {

}

ConsoleController_N::ConsoleCtrl::~ConsoleCtrl()
{

}



std::string ConsoleController_N::ConsoleCtrl::GetFPS()
{
	std::string ans;

	std::string FPS = std::to_string((1.0 / fps.timeDiff) * fps.counter);
	std::string ms = std::to_string((fps.timeDiff / fps.counter) * 1000);
	ans = FPS + "FPS / " + ms + "ms";

	return ans;
}



