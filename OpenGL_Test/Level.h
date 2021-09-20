#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <string>

namespace Levels
{
	class Level
	{
	public:
		struct lvl {
			std::string path;
			char map[5][5];
			glm::vec3 pos[5][5];
			glm::vec3 lightPos[2];
		};
		
		int cnrCounter; //helps stop when we have the fourth corner
		
		lvl Lvl;

		Level(std::string path);
		~Level();
		
		std::string ReadFile();		
		char ReturnMapCharacter(unsigned int i, unsigned int j);

		

	private:
		int counter = 0;;
	};
}