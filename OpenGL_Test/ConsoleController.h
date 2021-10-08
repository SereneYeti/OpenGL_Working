#include <string>

namespace ConsoleController_N
{
	struct FPS {
		double prevTime;
		double crntTime;
		double timeDiff;
		unsigned int counter;
	};
	struct ModelPos {
		int x;
		int y; 
		int z;
	};
	class ConsoleCtrl
	{
	public:
		FPS fps;
		bool spawnModel;
		ModelPos modelPos;
		std::string Commands(std::string command);
		ConsoleCtrl();
		~ConsoleCtrl();		

	private:
		std::string GetFPS();
	};
}