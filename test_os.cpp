#include <iostream>

int main() {
#ifdef _WIN32
	std::cout << "Windows" << std::endl;
#elif __linux__
	std::cout << "Linux" << std::endl;
#endif
}
