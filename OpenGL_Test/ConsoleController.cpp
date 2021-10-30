#include "ConsoleController.h"
#include "FileReader.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <vector>



using namespace ConsoleController_N;
using namespace FileReader;

Reader fileReader;

std::string ConsoleController_N::ConsoleCtrl::Commands(std::string command)
{
	std::string ans = "";
	transform(command.begin(), command.end(), command.begin(), std::tolower); //ensures that all input is lowercase to prevent errors from llooking for a lowercase word that is in upercase.
	std::vector<std::string> words = fileReader.SplitString(command);
	//std::cout << command;
	if (words[0] == "fps") {
		std::cout << "Current Frames Per Second is: " << GetFPS() << std::endl;
	}
	else if (words[0] == "triangles") {
		std::cout << "Current number of trianlges in the scene is: " << triangleCount << std::endl;
	}
	else if (words[0] == "load") { //needs to check 1st word and store the 2nd word
		std::cout << "Loading Map File: " << words[1] << std::endl;
		mapName = words[1];
		loadLevel = true;
		ans = "load";
	}	
	else if (words[0] == "spawn") {  //needs to check 1st word and store the 2nd word
		//1 = X; 2 = Y 3 = Z
		std::cout << "Spawning Model..." << std::endl;
		modelName += words[1];
		modelPath += modelName;
		spawnModel = true;
		modelPos.x = std::stoi(words[2]);
		modelPos.y = std::stoi(words[3]);
		modelPos.z = std::stoi(words[4]);
		ans = "spawn";
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



