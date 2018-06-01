#include <iostream>
#include <stdexcept>
#include <string>
#include <dlfcn.h>
#include "libst.h"
#include "libdyn.h"

using my_func = void(*)(int);

template <typename T, typename U>
void dll_check(T actual, U bad, std::string const & msg) {
	if (actual == bad) {
		std::cerr << dlerror() << std::endl;
		throw std::runtime_error(msg);
	}
}

my_func load_func(void* handler, char const * fun) {
	my_func f = reinterpret_cast<my_func>(dlsym(handler, fun));
	dll_check(f, nullptr, "Couldn't load function from dynamic loaded library");
	return f;
}

int main() {
	hello("World");
	nihao("Dima");
	dyn_f();
	dyn_g();
	void* handler = dlopen("./lib/librldyn/librldyn.so", RTLD_LAZY);
	dll_check(handler, nullptr, "Couldn't load dynamic library");
	load_func(handler, "foo")(42);
	load_func(handler, "bar")(24);
	dll_check(dlclose(handler) == 0, false, "Couldn't close dynamic library handler");
	return 0;
}