#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <string>
#include <list>

namespace FileReader
{
	struct Model_data {
		std::string name;
		std::string path;
		glm::vec3 pos;
		glm::vec3 rot;
		glm::vec3 scale;
	};
	
	class Reader
	{
	public:

		Model_data ReadModelData(std::string path);
		Reader();		

	private:
		
	};
}