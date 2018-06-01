GCC=g++ -Wall -Wextra -pedantic -std=c++11
#static_lib variables:
STLIB_PATH=lib/libst
STLIB=$(STLIB_PATH)/libst.a
STLIB_SRC=$(STLIB_PATH)/src/*.cpp
STLIB_OBJ=$(STLIB_PATH)/*.o
ADD_ST_LIB=-Ilib/libst/include -L$(STLIB_PATH) -lst
#dynamic_lib variables:
DYNLIB_PATH=lib/libdyn
DYNLIB=$(DYNLIB_PATH)/libdyn.so
DYNLIB_SRC=$(DYNLIB_PATH)/src/*.cpp
ADD_DYN_LIB=-Ilib/libdyn/include -L$(DYNLIB_PATH) -Wl,-rpath,$(DYNLIB_PATH) -ldyn
#runtime_loaded_dynamic_lib variables:
RLDYNLIB_PATH=lib/librldyn
RLDYNLIB=$(RLDYNLIB_PATH)/librldyn.so
RLDYNLIB_SRC=$(RLDYNLIB_PATH)/src/*.cpp

RLLINKING_LIB=-ldl

all: main

run: all
	./main

clean:
	rm -f $(STLIB_OBJ) $(STLIB) $(DYNLIB) $(RLDYNLIB) main

main: $(STLIB) $(DYNLIB) $(RLDYNLIB)
	$(GCC) main.cpp $(ADD_ST_LIB) $(ADD_DYN_LIB) $(ADD_RLDYN_LIB) $(RLLINKING_LIB) -o main

$(STLIB): $(STLIB_OBJ)
	ar rsc $(STLIB) $(STLIB_OBJ)

$(STLIB_OBJ):
	cd $(STLIB_PATH); \
	$(GCC) -c src/*.cpp; \
	cd ./../..

$(DYNLIB):
	$(GCC) -shared -fPIC $(DYNLIB_SRC) -o $(DYNLIB)

$(RLDYNLIB):
	$(GCC) -shared -fPIC $(RLDYNLIB_SRC) -o $(RLDYNLIB)