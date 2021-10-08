#include "FileReader.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <vector>

using namespace FileReader;

//TO DO: REDO MATERIAL LIST TO READ FROM A FILE SEPARATED BY COMA'S
//----------------------------------------------------------------

Model_data Reader::ReadModelData(std::string path) {

	Model_data ans;
	std::ifstream myFileStream(path);
	std::string line;
	std::string temp;

	std::string pos;
	std::string pos1;
	std::string pos2;
	std::string pos3;
	std::string rot;
	std::string rot1;
	std::string rot2;
	std::string rot3;
	std::string scale;
	std::string scale1;
	std::string scale2;
	std::string scale3;

	if (!myFileStream.is_open()) {
		std::cout << "File Failed To Open";
		return ans;
	}

	while (std::getline(myFileStream,line))
	{
		std::stringstream ss(line);
		std::getline(ss, ans.name, ',');
		std::getline(ss, ans.path, ',');
		std::getline(ss, pos, ',');
		std::stringstream ss2(pos);
		std::getline(ss2, pos1, ' ');
		std::getline(ss2, pos2, ' ');
		std::getline(ss2, pos3, ' ');
		std::getline(ss, rot, ',');
		ss2 = std::stringstream(rot);
		std::getline(ss2, rot1, ' ');
		std::getline(ss2, rot2, ' ');
		std::getline(ss2, rot3, ' ');
		std::getline(ss, scale, ',');
		ss2 = std::stringstream(scale);
		std::getline(ss2, scale1, ' ');
		std::getline(ss2, scale2, ' ');
		std::getline(ss2, scale3, ' ');
	}

	myFileStream.close();

	ans.pos = glm::vec3(std::stoi(pos1), std::stoi(pos2), std::stoi(pos3));
	ans.rot = glm::vec3(std::stoi(rot1), std::stoi(rot2), std::stoi(rot3));
	ans.scale = glm::vec3(std::stoi(scale1), std::stoi(scale2), std::stoi(scale3));
	/*std::cout << "Pos1: " << pos1 << std::endl << "P0s2: " << pos2 << "P0s3: " 
		<< pos3 << "rot1: " << rot1 << std::endl << "rot2: " << rot2 << "rot3: " << rot3 << "SCALE - " << scale
		<< "scale1: " << scale1 << std::endl << "scale2: " << scale2 << "scale3: " << scale3;*/

	return ans;
}

FileReader::Reader::Reader()
{
}

std::vector<std::string> FileReader::Reader::SplitString(std::string StringToSplit)
{
	std::vector<std::string> words;
	std::string line;

	std::stringstream ss(StringToSplit);
	
	while (ss >> line)
	{ 
		//ss = std::stringstream(StringToSplit);
		//ss.getline(ss, line, " ");
		words.push_back(line);		
	}
	std::cout << "SIZE: " << words.size();
	return words;
}
