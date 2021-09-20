#include <string>
namespace Levels
{
	class Level
	{
	public:
		
		Level();
		~Level();

		std::string ReadFile(std::string);

	private:
		float test = 0.2f;
	};
}