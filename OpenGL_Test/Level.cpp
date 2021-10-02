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

	file.open(lvl_Structure.path.c_str());
	if (file.is_open() == true) {
		while (std::getline(file,line)&&counter < lvl_Structure.sizeX)
		{			
			for (int i = 0; i < line.length(); i++) {
				lvl_Structure.lvlSize++;
				lvl_Structure.map[i][counter] = line[i];
				std::cout << lvl_Structure.map[i][counter];
				lvl_Structure.posArr[i][counter] = SetPosArr(line[i],i,counter);
				//std::cout << "-" << lvl_Structure.lvlSize << "-" << std::endl;
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

glm::vec3 Level::ReturnPosition(int i, int j) {
	return lvl_Structure.posArr[i][j];
}

char Level::ReturnMapCharacter(unsigned int i, unsigned int j) {
	if(i < lvl_Structure.sizeX && j < lvl_Structure.sizeZ)
		return lvl_Structure.map[i][j];
}
glm::vec3 Level::SetPosArr(char character, int i, int j) {
	if (i < lvl_Structure.sizeX && j < lvl_Structure.sizeZ)
	{
		if (character == '[') //Top Left Corner
		{
			return glm::vec3(i, 1.0f, j);			
		}
		if (character == ']') //Top Right Corner
		{
			return glm::vec3(i, 1.0f, j);
		}
		if (character == '{') //Bottom Left Corner
		{
			return glm::vec3(i, 1.0f, j);
		}
		if (character == '}') //Bottom Right Corner
		{
			return glm::vec3(i, 1.0f, j);
		}
		if (character == 'T') { //Top Wall
			return glm::vec3(i, 1.0, j);
		}
		if (character == 'B') { // Bottom Wall
			return glm::vec3(i, 1.0, j);
		}
		if (character == 'L') { //Left Wall
			return glm::vec3(i, 1.0, j);
		}
		if (character == 'R') { //Right Wall
			return glm::vec3(i, 1.0, j);
		}
		if (character == 'C') { //Roof therefore has a floor as well
			return glm::vec3(i, -1.0, j);
		}
		if (character == 'P')  //Floor - has no roof
		{
			return glm::vec3(i, -1.0, j);
		}
		if (character == 'S') { //Light - NB: While this is light there will also always be a floor spawned underneath it as well.
			SetLightPos( i, j);
			return glm::vec3(i, -1.0, j);
		}
		if (character == 'D') { //Where a 'Door' will be
			return glm::vec3(i, -1.0, j);
		}
	}
}
std::vector<glm::vec3> Level::SettupPosArr( ) {
	std::vector<glm::vec3> arr;
	for (int i = 0; i < lvl_Structure.sizeX; i++) {
		for (int j = 0; j < lvl_Structure.sizeZ; j++)
		{
			if (ReturnMapCharacter(i, j) == 'T')
			{
				int pos = 1;
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos-1, j));
				arr.push_back(glm::vec3(i, pos+1, j));
				
			}
			if (ReturnMapCharacter(i, j) == 'B')
			{
				int pos = 1;
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos - 1, j));
				arr.push_back(glm::vec3(i, pos + 1, j));
				         
			}
			if (ReturnMapCharacter(i, j) == 'L')
			{
				int pos = 1;
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos - 1, j));
				arr.push_back(glm::vec3(i, pos + 1, j));				  
			}
			if (ReturnMapCharacter(i, j) == 'R')
			{
				int pos = 1;
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos - 1, j));
				arr.push_back(glm::vec3(i, pos + 1, j));
				   
			}   
			if (ReturnMapCharacter(i, j) == '[') //Top Left Corner
			{
				int pos = 1;
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos - 1, j));
				arr.push_back(glm::vec3(i, pos + 1, j));
			}
			if (ReturnMapCharacter(i, j) == ']') //Top Right Corner
			{
				int pos = 1;
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos - 1, j));
				arr.push_back(glm::vec3(i, pos + 1, j));
			}
			if (ReturnMapCharacter(i, j) == '{') //Bottom Left Corner
			{
				int pos = 1;
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos - 1, j));
				arr.push_back(glm::vec3(i, pos + 1, j));
			}
			if (ReturnMapCharacter(i, j) == '}') //Bottom Right Corner
			{
				int pos = 1;;
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos - 1, j));
				arr.push_back(glm::vec3(i, pos + 1, j));
			}     
			if (ReturnMapCharacter(i, j) == 'C') //Ceiling (C) and Light (S)
			{
				int pos = -1;				
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos + 4, j));				
				            
			}
			if (ReturnMapCharacter(i, j) == 'S') // Light (S)
			{
				int pos = -1;
				SetLightPos(i, j);
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos + 4, j));

			}
			if (ReturnMapCharacter(i, j) == 'P') //Floor with no roof
			{                
				int pos = -1;				
				arr.push_back(glm::vec3(i, pos, j));
			}		
			if (ReturnMapCharacter(i, j) == 'D') //Floor & Therefore Roof
			{
				int pos = -1;
				arr.push_back(glm::vec3(i, pos, j));
				arr.push_back(glm::vec3(i, pos + 4, j));

			}
		}
	}

	return arr;
}

void Level::SetLightPos(int i, int j) {
	
	if (lightCounter < lvl_Structure.numLights)
	{
		lvl_Structure.lightPos[lightCounter] = glm::vec3(i, 2.0f, j);
		//std::cout << "-" << lvl_Structure.lightPos[lightCounter].x << "-" << std::endl;
	}
}

glm::vec3 Level::DetermineRotation(int i, int j) {
	if (ReturnMapCharacter(i, j) == 'T')
	{
		return glm::vec3(1.0f, 0.0f, 0.0f);
	}
	if (ReturnMapCharacter(i, j) == 'B')
	{
		return glm::vec3(-1.0f, 0.0f, 0.0f);
	}
	if (ReturnMapCharacter(i, j) == 'L')
	{
		return glm::vec3(0.0f, 0.0f, -1.0f);
	}
	if (ReturnMapCharacter(i, j) == 'R')
	{
		return glm::vec3(0.0f, 0.0f, 1.0f);

	}
	if (ReturnMapCharacter(i, j) == '[') //Top Left Corner
	{
		return glm::vec3(0.0f, 0.0f, -1.0f);
	}
	if (ReturnMapCharacter(i, j) == ']') //Top Right Corner
	{
		return glm::vec3(0.0f, 0.0f, 1.0f);
	}
	if (ReturnMapCharacter(i, j) == '{') //Bottom Left Corner
	{
		return glm::vec3(0.0f, 0.0f, -1.0f);
	}
	if (ReturnMapCharacter(i, j) == '}') //Bottom Right Corner
	{
		return glm::vec3(0.0f, 0.0f, 1.0f);
	}
	if (ReturnMapCharacter(i, j) == 'D') //Floor & Therefore Roof
	{
		if (ReturnMapCharacter(i, j + 1) == 'L')
			return glm::vec3(0.0f, 0.0f, -1.0f);
		else if (ReturnMapCharacter(i, j + 1) == 'R')
			return glm::vec3(0.0f, 0.0f, 1.0f);
	}
}
	
Level::Level(std::string path, int x, int z, int numLights) {
	this ->lvl_Structure.path = path;
	this->lvl_Structure.sizeX = x;
	this->lvl_Structure.sizeZ = z;
	this->lvl_Structure.numLights = numLights;

}
Level::~Level() {

}