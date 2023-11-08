#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <ctype.h>

enum {
	NONE        = 0x0,
	BINARY      = 0x2,
	DECIMAL     = 0xA,
	HEXADECIMAL = 0x10,
};

uint64_t readx(char *str, unsigned input, int *err) {
	static char letters[] = "0123456789ABCDEF";

	uint64_t x = 0;
	for (char *c = str; *c; c++) {
		*c = toupper(*c);
		char *d = strchr(letters, *c);
		if (!d || d - letters >= input) {
			*err = 1;
			break;
		}
		x = input * x + (d - letters);
	}
	return x;
}

int main(int argc, char **argv) {
	unsigned output = NONE;

	char *str = NULL;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (strchr(argv[i], 'b'))
				output = BINARY;
			if (strchr(argv[i], 'd'))
				output = DECIMAL;
			if (strchr(argv[i], 'x'))
				output = HEXADECIMAL;
		}
		else
			str = argv[i];

	}

	if (!str) {
		printf("error: no integer\n");
		return 1;
	}

	uint64_t x;
	unsigned input = NONE;
	int err = 0;
	if (strlen(str) < 3) {
		input = DECIMAL;
	}
	else if (str[1] == 'b') {
		input = BINARY;
		str += 2;
	}
	else if (str[1] == 'x') {
		input = HEXADECIMAL;
		str += 2;
	}
	else {
		input = DECIMAL;
	}

	x = readx(str, input, &err);
	if (err) {
		printf("error: bad integer\n");
		return 2;
	}

	if (output == BINARY) {
		printf("0b");
		int flag = 0;
		for (int i = 63; i >= 0; i--) {
			uint64_t bit = 1ull << i;
			if (x & bit)
				flag = 1;

			if (flag)
				printf("%c", x & bit ? '1' : '0');
		}
		printf("\n");
	}
	if (output == DECIMAL) {
		printf("%" PRIu64 "\n", x);
	}
	if (output == HEXADECIMAL)
		printf("0x%" PRIX64 "\n", x);
	return 0;
}
