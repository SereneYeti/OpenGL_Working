#include "Level.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace Levels;

std::string Level::ReadFile() {
	std::string ans = "";
	std::fstream file;
	std::string line = "";
	std::cout << "The map is: " << std::endl;

	file.open(Lvl.path.c_str());
	if (file.is_open() == true) {
		while (std::getline(file,line)&&counter < 5)
		{			
			for (int i = 0; i < line.length(); i++) {
				Lvl.map[i][counter] = line[i];
				std::cout << Lvl.map[i][counter];
			}
			std::cout << std::endl;
			counter++;
		}
		file.close();
	}
	else {
		std::cout << "ERROR - File not found!" << std::endl;
	}
	return ans;
}

char Level::ReturnMapCharacter(unsigned int i, unsigned int j) {
	if(i < 5 && j < 5)
		return Lvl.map[i][j];
}

Level::Level(std::string path) {
	this ->Lvl.path = path;

}
Level::~Level() {


}