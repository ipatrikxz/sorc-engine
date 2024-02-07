
#include <fstream>
#include <string>

/*
*	Util
*
*	Contains utility functions, such as reading shader source code from files.
*/
namespace Util {

	inline std::string ReadTextFromFile(std::string path) {
		std::ifstream file(path);
		std::string str;
		std::string line;
		while (std::getline(file, line)) {
			str += line + "\n";
		}
		return str;
	}
}