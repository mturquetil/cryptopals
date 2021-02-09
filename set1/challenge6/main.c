#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// print_histogram {{{
void print_histogram (char_freq * freq, int freq_size, int str_size) {
	for (int i = 0; i < sizeof(frequent_char) - 1; i++) {
		for (int j = 0; j < freq_size; j++) {
			if (freq[j].c == frequent_char[i]) {
				printf("%c: ", frequent_char[i]);
				for (int k = 0; k < freq[j].count; k++) {
					printf("=");
				}
				printf("\n");
			}
		}
	}
}
// }}}

// get_frequency {{{
int get_frequency(char_freq *freq, char * str, int str_size) {
	int freq_size = 0;

	for (int i = 0; i < str_size; i++) {
		freq[freq_size].c = str[i];
		freq[freq_size].count = 1;

		while (str[i + 1] == str[i] && i < str_size) {
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
float check_readability (char * str, int str_size) {
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

	return ((float) count * 100) / str_size;
}
// }}}

// get_secret {{{
void get_secret(char c, char * original, int orig_size) {
	char xor_char;
	char secret[orig_size];
	char sorted[orig_size];

	//for (int k = 0; k < orig_size; k++) {
	//	printf("%d ", original[k]);
	//}

	int i, j;

	for (i = 0; i < strlen(frequent_char); i++) {
		xor_char = c ^ frequent_char[i];

		for (j = 0; j < orig_size; j++) {
			secret[j] = original[j] ^ xor_char;
		}

		secret[j] = '\0';

		for (int k = 0; k < sizeof(secret); k++) {
			sorted[k] = secret[k];
		}

		qsort(sorted, sizeof(sorted), sizeof(*sorted), compare_char);

		char_freq plain_freq[sizeof(sorted)];
		int freq_size = 0;
		freq_size = get_frequency(plain_freq, sorted, sizeof(sorted));

		print_histogram(plain_freq, freq_size, orig_size);
	}
}
// }}}

// calc_hamming {{{
int calc_hamming (char * str1, char * str2, int str1_size, int str2_size) {
	if (str1_size != str2_size) {
		printf("length not matching");
		exit(EXIT_FAILURE);
	}

	int hamming = 0;
	int str_size = str1_size;


	char ham[str_size];

	for (int i = 0; i < str_size; i++) {
		ham[i] = str1[i] ^ str2[i];
	}

	for (int i = 0; i < str_size; i++) {
		for (int j = 0; j < 8; j++) {
			if (1 && (ham[i] & (1 << j))) {
				hamming++;
			}
		}
	}

	return hamming;
}
// }}}

// get_keysize {{{
int get_keysize(int chunks, char * line, int max_key) {
	int key = 0;
	float min_distance = 0;

	for (int keysize = 2; keysize < max_key; keysize++) {
		int hamming = 0;
		float distance = 0;
		char str1[keysize];
		char str2[keysize];
		int i;

		for (int chunk = 0; chunk < chunks; chunk++) {
			for (i = 0 + (2 * chunk * keysize); i < keysize + (2 * chunk * keysize); i++) {
				str1[i - (2 * chunk * keysize)] = line[i];
			}

			for (i = 0 + keysize + (2 * chunk * keysize); i < keysize * 2 + (2 * chunk * keysize); i++) {
				str2[i - (keysize + (2 * chunk * keysize))] = line[i];
			}

			hamming += calc_hamming(str1, str2, sizeof(str1), sizeof(str2));
		}


		distance = hamming / keysize;

		if (min_distance > distance || min_distance == 0) {
			min_distance = distance;
			key = keysize;
		}
	}

	return key;
}
// }}}

// main {{{
int main () {
	const int CHUNKS = 1;

	int keysize = 0;
	int line_len = 0;
	size_t buffersize = 2900;

	char * data;
	int data_size = 0;
	data = malloc(buffersize);

	char * line;
	line = malloc(buffersize);

	FILE *file;
	int j = 0;

	file = fopen("challenge", "r");

	// get file data {{{
	while ((line_len = getline(&line, &buffersize, file)) != -1) {
		for (int i = 0; i < line_len; i++) {
			data[j] = line[i];
			j++;
		}

		data_size += line_len;
	}
	// }}}

	free(line);

	// for (int i = 0; i < 40; i += 2) {
	// 	keysize = get_keysize(CHUNKS + i, data, 20);
	// }

	keysize = 29;

	// block creation && transposition {{{
	const int CONTENT_SIZE = 80;
	char blocks[CONTENT_SIZE][keysize];
	char transposition[keysize][CONTENT_SIZE];

	// blocks creation {{{
	for (int i = 0; i < CONTENT_SIZE; i++) {
		for (int j = 0; j < keysize; j++) {
			blocks[i][j] = data[j + (i * keysize)];
		}
		printf("%d ", blocks[i][9]);
	}
	printf("\n");
	// }}}

	// transposing blocks {{{
	for (int i = 0; i < keysize; i++) {
		for (int j = 0; j < CONTENT_SIZE; j++) {
			transposition[i][j] = blocks[j][i];
		}
	}
	// }}}

	// }}}

	for (int i = 0; i < 29; i++) {
		char sorted[sizeof(transposition[i])];

		int freq_size = 0;
		char_freq freq[sizeof(sorted)];

		for (int k = 0; k < sizeof(transposition[i]); k++) {
			sorted[k] = transposition[i][k];
		}

		qsort(sorted, sizeof(sorted), sizeof(*sorted), compare_char);

		// get frequency of encoded first letters
		freq_size = get_frequency(freq, sorted, sizeof(sorted));

		for (int j = 0; j < 1; j++) {
			// its my second question, why I could have the key like this
			if (freq[j].c < 96) {
				freq[j].c += 32;
			} else {
				freq[j].c -= 32;
			}

			printf("%c", freq[j].c);

			// get_secret(freq[j].c, transposition[i], sizeof(transposition[i]));
		}
	}

	fclose(file);
	free(data);

	return 0;
}
// }}}
