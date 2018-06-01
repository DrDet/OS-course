#include <iostream>

extern "C" {	
	void foo(int x) {
		std::cout << "Hello from foo(int) run time loaded dynamic library function: " << x << std::endl;
	}
}