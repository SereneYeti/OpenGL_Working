#include <string>

namespace ConsoleController_N
{
	struct FPS {
		double prevTime;
		double crntTime;
		double timeDiff;
		unsigned int counter;
	};
	class ConsoleCtrl
	{
	public:
		FPS fps;
		std::string Commands(std::string command);
		ConsoleCtrl();
		~ConsoleCtrl();		

	private:
		std::string GetFPS();
	};
}