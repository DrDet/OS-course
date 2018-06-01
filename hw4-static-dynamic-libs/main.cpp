#include <iostream>
#include <stdexcept>
#include <cstring>
#include <dlfcn.h>
#include "libst.h"
#include "libdyn.h"

using std::cerr;
using std::endl;
using std::runtime_error;

using my_func = void(*)(int);

my_func load_func(char const * fun) {
	void* handler = dlopen("./lib/librldyn/librldyn.so", RTLD_LAZY);
	if (handler == nullptr) {
		cerr << strerror(errno) << endl;
		throw runtime_error("Couldn't load dynamic library");
	}
	my_func f = reinterpret_cast<my_func>(dlsym(handler, fun));
	if (f == nullptr) {
		cerr << dlerror() << endl;
		throw runtime_error("Couldn't load function from dynamic loaded library");
	}
	return f;
}

int main() {
	hello("World");
	nihao("Dima");
	dyn_f();
	dyn_g();
	load_func("foo")(42);
	load_func("bar")(24);
	return 0;
}