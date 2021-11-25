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
		try
		{
			mapName = words[1];
		}
		catch (const std::exception& e)
		{
			std::cout << "Unable to find File Name to Load File.\nException Code: " << e.what() << std::endl;
		}
		
		loadLevel = true;
		ans = "load";
	}	
	else if (words[0] == "spawn") {  //needs to check 1st word and store the 2nd word
		//1 = X; 2 = Y 3 = Z
		//std::cout << "Spawning Model..." << std::endl;
		modelName = words[1];
		//modelPath += modelName;
		spawnModel = true;
		try
		{
			if (words.size() == 5)
			{
				modelPos.x = std::stoi(words[2]);
				modelPos.y = std::stoi(words[3]);
				modelPos.z = std::stoi(words[4]);
			}
			
		}
		catch (const std::exception& e)
		{
			modelPos.x = 1;
			modelPos.y = 1;
			modelPos.z = 1;
			std::cout << "Unable to assign Co-ordinates Spawning at (1 1 1).\nException Code: " << e.what() << std::endl;
		}
		
		ans = "spawn";
	}
	else if (words[0] == "!help") {  //needs to check 1st word and store the 2nd word
		std::cout << "COMANDS: " << "\n!help - Get a list of the available commands\nfps - Get the programs current fps"
			<< "\nspawn modelname.obj pos1 pos2 pos3 - Spawns the specified model at the specified co-ordinates."
			<< "\nload mapname.txt - loads the specified map.\ntriangles - Gets the total amount of triangles currently active within the scene" << std::endl;
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



