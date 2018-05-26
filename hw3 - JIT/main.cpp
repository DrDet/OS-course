#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>

/*Function to call:*/
//int f(int x, int y) {
//	return x + y;
//}

/*objdump of f.o*/
//f.o:     file format elf64-x86-64
//Disassembly of section .text:
//0000000000000000 <_Z1fii>:
//   0:   55                      push   %rbp
//   1:   48 89 e5                mov    %rsp,%rbp
//   4:   89 7d fc                mov    %edi,-0x4(%rbp)
//   7:   89 75 f8                mov    %esi,-0x8(%rbp)
//   a:   8b 55 fc                mov    -0x4(%rbp),%edx
//   d:   8b 45 f8                mov    -0x8(%rbp),%eax
//  10:   01 d0                   add    %edx,%eax
//  12:   5d                      pop    %rbp
//  13:   c3                      retq

/*Machine code of f:*/
size_t const LEN = 20;
char const machine_code[LEN] = {
   0x55,
   0x48, 0x89, 0xe5,
   0x89, 0x7d, 0xfc,
   0x89, 0x75, 0xf8,
   0x8b, 0x55, 0xfc,
   0x8b, 0x45, 0xf8,
   0x01, 0xd0,
   0x5d,
   0xc3
};

typedef int(*my_func)(int, int);

template <typename T>
void check(T const status, T const bad_status, char const * error_msg) {
	if (status == bad_status) {
		perror(error_msg);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char* argv[]) {
	check(argc != 3, true, "Incorrect input format.\nUsage: main <num1> <num2>");
	int a = atoi(argv[1]),
		b = atoi(argv[2]);
	char* ptr = static_cast<char*>(mmap(NULL, LEN, PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0));
	check(ptr == MAP_FAILED, true, "Couldn't allocate memory");
	memcpy(ptr, machine_code, LEN);
	check(mprotect(ptr, LEN, PROT_EXEC | PROT_READ), -1, "Couldn't set protection");
	my_func f = reinterpret_cast<my_func>(ptr);
	printf("%d\n", f(a, b));
	check(munmap(ptr, LEN), -1, "Couldn't free memory");
	return 0;
}