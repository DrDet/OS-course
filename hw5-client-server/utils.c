#include <stdlib.h>
#include <stdio.h>

void check(int actual, int val_to_cmp, int is_good, char const * msg) {
	if (is_good && actual != val_to_cmp || !is_good && actual == val_to_cmp) {
		perror(msg);
		exit(EXIT_FAILURE);
	}
}