#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <string>

namespace Levels
{
	struct LevelStructure {
		std::string path;
		int sizeX; int sizeZ; int numLights; int lvlSize;
		char map[5][5];
		glm::vec3 posArr[5][5];
		glm::vec3 rotation[5][5];
		glm::vec3 lightPos[2];
	};

	class Level
	{
	public:			
		
		LevelStructure lvl_Structure;		

		Level(std::string path, int x, int z, int numLights);
		~Level();
		
		std::string ReadFile();	
		glm::vec3 ReturnPosition(int i, int j);
		char ReturnMapCharacter(unsigned int i, unsigned int j);

	private:	
		int counter = 0;
		int lightCounter = 0;		
		glm::vec3 SetPosArr(char character, int i, int j);		
		void SetLightPos(char character, int i, int j);
		glm::vec3 DetermineRotation(int i, int j) {
            if (level.ReturnMapCharacter(i, j) == 'T')
            {
                return glm::vec3(1.0f, 0.0f, 0.0f);
            }
            if (level.ReturnMapCharacter(i, j) == 'B')
            {
                return glm::vec3(-1.0f, 0.0f, 0.0f);
            }
            if (level.ReturnMapCharacter(i, j) == 'L')
            {               
                return glm::vec3(0.0f, 0.0f, -1.0f);
            }
            if (level.ReturnMapCharacter(i, j) == 'R')
            {
                return glm::vec3(0.0f, 0.0f, 1.0f);

            }
            if (level.ReturnMapCharacter(i, j) == '[') //Top Left Corner
            {              
                return glm::vec3(0.0f, 0.0f, -1.0f);
            }
            if (level.ReturnMapCharacter(i, j) == ']') //Top Right Corner
            {
                return glm::vec3(0.0f, 0.0f, 1.0f);
            }
            if (level.ReturnMapCharacter(i, j) == '{') //Bottom Left Corner
            {
                return glm::vec3(0.0f, 0.0f, -1.0f);
            }
            if (level.ReturnMapCharacter(i, j) == '}') //Bottom Right Corner
            {
                return glm::vec3(0.0f, 0.0f, 1.0f);
            }           
            if (level.ReturnMapCharacter(i, j) == 'D') //Floor & Therefore Roof
            {
                if (level.ReturnMapCharacter(i, j + 1) == 'L')
                    return glm::vec3(0.0f, 0.0f, -1.0f);
                else if (level.ReturnMapCharacter(i, j + 1) == 'R')
                    return glm::vec3(0.0f, 0.0f, 1.0f);
            }
		}
	};
}