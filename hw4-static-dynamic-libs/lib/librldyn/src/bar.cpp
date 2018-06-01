#include <iostream>

extern "C" {
	void bar(int x) {
		std::cout << "Hello from bar(int) run time loaded dynamic library function: " << x << std::endl;
	}
}