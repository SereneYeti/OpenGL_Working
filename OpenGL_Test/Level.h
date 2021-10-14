#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <string>
#include <vector>

namespace Levels
{
	struct LevelStructure {
		std::string path;
		std::string name;
		int sizeX; int sizeZ; int numLights; int lvlSize;
		char map[15][15];
		glm::vec3 posArr[15][15];
		glm::vec3 rotation[15][15];
		glm::vec3 lightPos[7];
	};

	class Level
	{
	public:

		LevelStructure lvl_Structure;

		Level(std::string path, int x, int z, int numLights);
		~Level();
		glm::vec3 DetermineRotation(int i, int j);
		std::string ReadFile();
		glm::vec3 ReturnPosition(int i, int j);
		char ReturnMapCharacter(unsigned int i, unsigned int j);
		std::vector<glm::vec3> SettupPosArr();

	private:
		int counter = 0;
		int lightCounter = 0;
		glm::vec3 SetPosArr(char character, int i, int j);
		
		void SetLightPos(int i, int j);
	};
}