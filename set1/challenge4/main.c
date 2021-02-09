#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char frequent_char[] = { 'e', 't', 'a', 'o', 'i', 0 };

typedef struct {
	char c;
	int count;
} char_freq;

// compare_struct {{{
int compare_struct(const void *a, const void *b) {
	char_freq *x = (char_freq *)a;
	char_freq *y = (char_freq *)b;

	return (y->count - x->count);
}
// }}}

// compare_char {{{
int compare_char(const void *a, const void *b) {
	char *x = (char *) a;
	char *y = (char *) b;

	return *x - *y;
}
// }}}

// get_decimal {{{
int get_decimal(char hexstring[], int index) {
	int decimal = 0;

	if (hexstring[index] >= '0' && hexstring[index] <= '9') {
		decimal = hexstring[index] - '0';
	} else if (hexstring[index] >= 'a' && hexstring[index] <= 'f') {
		decimal = hexstring[index] - 'a' + 10;
	} else if (hexstring[index] >= 'A' && hexstring[index] <= 'F') {
		decimal = hexstring[index] - 'A' + 10;
	}

	return decimal;
}
// }}}

// hex2decimal {{{
void hex2decimal (char hexstring[], char * str) {
	for (int i = 0; i < strlen(hexstring); i += 2) {
		int f1 = get_decimal(hexstring, i);
		int f2 = get_decimal(hexstring, i + 1);

		*str++ = f1 * 16 + f2;
	}

	*str++ = '\0';
}
// }}}

// get_frequency {{{
int get_frequency(char_freq *freq, char * str) {
	int freq_size = 0;

	for (int i = 0; i < strlen(str); i++) {
		freq[freq_size].c = str[i];
		freq[freq_size].count = 1;

		while (str[i + 1] == str[i] && i < strlen(str)) {
			freq[freq_size].count++;
			i++;
		}

		freq_size++;
	}

	qsort(freq, freq_size, sizeof(char_freq), compare_struct);

	return freq_size;
}
// }}}

// check_readability {{{
float check_readability (char * str, int debug, int str_size) {
	int count = 0;


	for (int i = 0; i < str_size; i++) {
		if (
				(str[i] >= 'a' && str[i] <= 'z') ||
				(str[i] >= 'A' && str[i] <= 'Z') ||
				(str[i] >= '0' && str[i] <= '9') ||
				(str[i] == 32)
		) {
			count++;
		}
	}

	if (debug) {
		// printf("len: %d\n", strlen(str));
	}

	return ((float) count * 100) / str_size;
}
// }}}

// get_secret {{{
void get_secret(char c, char * original, int orig_size) {
	char xor_char;
	char secret[orig_size];
	float readability = 0.0;

	int i, j;

	for (i = 0; i < strlen(frequent_char); i++) {
		xor_char = c ^ frequent_char[i];

		for (j = 0; j < orig_size; j++) {
			secret[j] = original[j] ^ xor_char;
		}

		secret[j] = '\0';

		readability = check_readability(secret, 0, sizeof(secret));

		if (readability > 90.0) {
			printf("secret:%sxor_char: %c (decimal: %d)", secret, xor_char, xor_char);
		}
	}
}
// }}}

int main () {
	FILE *file;
	char *line;
	size_t buffersize = 60;
	int count = 0;

	line = (char *)malloc(buffersize);

	file = fopen("chall4", "r");

	while (getline(&line, &buffersize, file) != -1) {
 		char original[strlen(line) / 2];
		char sorted[sizeof(original)];

		int freq_size = 0;
		char_freq freq[sizeof(sorted)];

		// sort letters in string
		hex2decimal(line, original);
		strncpy(sorted, original, sizeof(original));
		qsort(sorted, sizeof(sorted) - 1, sizeof(*sorted), compare_char);

		freq_size = get_frequency(freq, sorted);

		for (int i = 0; i < 3; i++) {
			get_secret(freq[i].c, original, sizeof(original));
		}

		count++;
	}
}
