#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const int s_box[16][16] = {
	{ 0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76 },
	{ 0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0 },
	{ 0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15 },
	{ 0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75 },
	{ 0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84 },
	{ 0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf },
	{ 0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8 },
	{ 0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2 },
	{ 0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73 },
	{ 0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb },
	{ 0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79 },
	{ 0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08 },
	{ 0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a },
	{ 0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e },
	{ 0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf },
	{ 0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 },
};

const int inv_sbox[16][16] = {
    { 0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb },
    { 0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb },
    { 0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e },
    { 0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25 },
    { 0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92 },
    { 0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84 },
    { 0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06 },
    { 0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b },
    { 0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73 },
    { 0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e },
    { 0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b },
    { 0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4 },
    { 0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f },
    { 0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef },
    { 0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61 },
    { 0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d },
};

const int mix_box[4][4] = {
	{ 0x02, 0x03, 0x01, 0x01 },
	{ 0x01, 0x02, 0x03, 0x01 },
	{ 0x01, 0x01, 0x02, 0x03 },
	{ 0x03, 0x01, 0x01, 0x02 },
};

const int inv_mix_box[4][4] = {
	{ 0x0E, 0x0B, 0x0D, 0x09 },
	{ 0x09, 0x0E, 0x0B, 0x0D },
	{ 0x0D, 0x09, 0x0E, 0x0B },
	{ 0x0B, 0x0D, 0x09, 0x0E },
};

const int round_constant[4] = { 0x01, 0x00, 0x00, 0x00 };

const int M_SIZE = 4;

// add_roundkey {{{
void add_roundkey(int roundkey[M_SIZE][M_SIZE], int key[M_SIZE][M_SIZE], int round_n) {
	int rc[4];

	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			roundkey[i][j] = key[i][j];
		}

		rc[i] = round_constant[i];
	}

	for (int r = 0; r < round_n; r++) {
		int temp_roundkey[M_SIZE][M_SIZE];

		for (int i = 0; i < M_SIZE; i++) {
			for (int j = 0; j < M_SIZE; j++) {
				temp_roundkey[i][j] = roundkey[i][j];
			}
		}

		for (int i = 0; i < M_SIZE; i++) {
			int gw3[4];

			roundkey[i][3] = temp_roundkey[(i + 1) % M_SIZE][3];
			int byte = roundkey[i][3];
			
			gw3[i] = s_box[byte >> 4][byte & 0x0f] ^ rc[i];

			roundkey[i][0] = gw3[i] ^ temp_roundkey[i][0];
			roundkey[i][1] = roundkey[i][0] ^ temp_roundkey[i][1];
			roundkey[i][2] = roundkey[i][1] ^ temp_roundkey[i][2];
			roundkey[i][3] = roundkey[i][2] ^ temp_roundkey[i][3];

		}

		rc[0] = (rc[0] & 0x80) ? ((rc[0] << 1) ^ 0x11b) : (rc[0] << 1);
	}
}
// }}}

// substitutes {{{
// substitute {{{
void substitute(int state[M_SIZE][M_SIZE]) {
	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			state[i][j] = s_box[state[i][j] >> 4][state[i][j] & 0x0f];
		}
	}
}
// }}}
// inv_sub {{{
void inv_sub(int state[M_SIZE][M_SIZE]) {
	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			state[i][j] = inv_sbox[state[i][j] >> 4][state[i][j] & 0x0f];
		}
	}
}
// }}}
// }}}

// shifts {{{
// shift {{{
void shift (int state[M_SIZE][M_SIZE]) {
	int temp_state[M_SIZE][M_SIZE];

	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			temp_state[i][j] = state[i][j];
		}
	}

	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			state[i][j] = temp_state[i][(j + i) % M_SIZE];
		}
	}
}
// }}}

// inv_shift {{{
void inv_shift (int state[M_SIZE][M_SIZE]) {
	int temp_state[M_SIZE][M_SIZE];

	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			temp_state[i][j] = state[i][j];
		}
	}

	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			state[i][(j + i) % M_SIZE] = temp_state[i][j];
		}
	}
}
// }}}
// }}}

// inv_mix {{{
void inv_mix(int state[M_SIZE][M_SIZE]) {
	int temp_state[M_SIZE][M_SIZE];

	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			temp_state[i][j] = state[i][j];
		}
	}

	for (int i = 0; i < 1; i++) {
		for (int j = 0; j < 1; j++) {
			int result = 0;

			for (int k = 0; k < 4; k++) {
				int byte = temp_state[k][j];

				temp_state[0][j] = 0x8e;
				temp_state[1][j] = 0x4d;
				temp_state[2][j] = 0xa1;
				temp_state[3][j] = 0xbc;

				printf("0: %x\n", (temp_state[0][j] << 1) ^ 0x11b);
				printf("1: %x\n", temp_state[1][j]);
				printf("2: %x\n", temp_state[2][j]);
				printf("3: %x\n", temp_state[3][j]);
				// printf("result: %x\n", temp_state[]);

				int remaining = (byte * ((inv_mix_box[i][k] / 2) && inv_mix_box[i][k] % 2));
				printf("byte shift by : %d\n", inv_mix_box[i][k]);

				// reducing polynomial
				// 	int mul = ((inv_mix_box[i][k] / 2) && byte & 0x80) ?
				// 		(byte << (inv_mix_box[i][k] / 2)) ^ 0x11b :
				// 		(byte << (inv_mix_box[i][k] / 2));

				// result ^= (mul ^ remaining);
			}

			// state[i][j] = result;
		}
	}
}
// }}}

// mix {{{
void mix(int state[M_SIZE][M_SIZE]) {
	int temp_state[M_SIZE][M_SIZE];

	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			temp_state[i][j] = state[i][j];
		}
	}

	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			int result = 0;

			for (int k = 0; k < 4; k++) {
				int byte = temp_state[k][j];

				int remaining = (byte * ((mix_box[i][k] / 2) && mix_box[i][k] % 2));

				// reducing polynomial
				int mul = ((mix_box[i][k] / 2) && byte & 0x80) ?
					(byte << (mix_box[i][k] / 2)) ^ 0x11b :
					(byte << (mix_box[i][k] / 2));

				result ^= (mul ^ remaining);
			}

			state[i][j] = result;
		}
	}
}
// }}}

// aes_decrypt {{{
void aes_decrypt(unsigned char ciphertext[], char key[], unsigned char plaintext[]) {
	int roundkey[M_SIZE][M_SIZE];
	int state[M_SIZE][M_SIZE];
	int key_m[M_SIZE][M_SIZE];

	for (int round_n = 0; round_n <= 0; round_n++) {
		// init
		if (round_n == 0) {
			for (int i = 0; i < M_SIZE; i++) {
				for (int j = 0; j < M_SIZE; j++) {
					state[j][i] = ciphertext[j + (i * M_SIZE)];
					key_m[j][i] = key[j + (i * M_SIZE)];
				}
			}

			add_roundkey(roundkey, key_m, 10);

			for (int i = 0; i < M_SIZE; i++) {
				for (int j = 0; j < M_SIZE; j++) {
					state[i][j] = state[i][j] ^ roundkey[i][j];
				}
			}


			inv_shift(state);

			inv_sub(state);

			add_roundkey(roundkey, key_m, 9);

			for (int i = 0; i < M_SIZE; i++) {
				for (int j = 0; j < M_SIZE; j++) {
					state[i][j] = state[i][j] ^ roundkey[i][j];
				}
			}

			printf("\n---after roundkey -----\n");

			for (int i = 0; i < M_SIZE; i++) {
				for (int j = 0; j < M_SIZE; j++) {
					printf("%x ", state[i][j]);
				}

				printf("\n");
			}
			printf("\n");

			inv_mix(state);

			printf("\n---after mix -----\n");

			for (int i = 0; i < M_SIZE; i++) {
				for (int j = 0; j < M_SIZE; j++) {
					printf("%x ", state[i][j]);
				}

				printf("\n");
			}
		} else {

			// rc[0] = (rc[0] & 0x80) ? ((rc[0] << 1) ^ 0x11b) : (rc[0] << 1);


			// if (round_n != 0) {
			// 	mix(state);
			// }

			// shift(state);
			// substitute(state);
		}
	}

	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			ciphertext[j + (i * M_SIZE)] = state[j][i];
		}
	}
}
// }}}

// aes_encrypt {{{
void aes_encrypt(char plaintext[], char key[], unsigned char ciphertext[]) {
	int roundkey[M_SIZE][M_SIZE];
	int state[M_SIZE][M_SIZE];
	int key_m[M_SIZE][M_SIZE];

	for (int round_n = 0; round_n <= 10; round_n++) {
		// init
		if (round_n == 0) {
			for (int i = 0; i < M_SIZE; i++) {
				for (int j = 0; j < M_SIZE; j++) {
					state[j][i] = plaintext[j + (i * M_SIZE)];
					key_m[j][i] = key[j + (i * M_SIZE)];
				}
			}

			add_roundkey(roundkey, key_m, round_n);

			for (int i = 0; i < M_SIZE; i++) {
				for (int j = 0; j < M_SIZE; j++) {
					state[i][j] = state[i][j] ^ roundkey[i][j];
				}
			}
		} else {
			substitute(state);
			shift(state);

			if (round_n != 10) {
				mix(state);
			}

			add_roundkey(roundkey, key_m, round_n);

			for (int i = 0; i < M_SIZE; i++) {
				for (int j = 0; j < M_SIZE; j++) {
					state[i][j] = state[i][j] ^ roundkey[i][j];
				}
			}
		}
	}

	for (int i = 0; i < M_SIZE; i++) {
		for (int j = 0; j < M_SIZE; j++) {
			ciphertext[j + (i * M_SIZE)] = state[j][i];
		}
	}
}
// }}}

int main () {
	char key[] = "Thats my Kung Fu";
	size_t buffersize = 100;

	int line_len = 0;
	int plaintext_size = 0;

	char *line;
	line = malloc(buffersize);

	char *plaintext;
	plaintext = malloc(buffersize);

	FILE *plaintext_file;
	int j = 0;

	plaintext_file = fopen("encrypted", "r");

	while ((line_len = getline(&line, &buffersize, plaintext_file)) != -1) {
        for (int i = 0; i < line_len; i++) {
            plaintext[j] = line[i];
            j++;
        }

        plaintext_size += line_len;
    }

	int blocks = ceil((plaintext_size) / 16.0);

	int content_size = blocks * 16;
	unsigned char ciphertext[content_size];

	// plaintext: 300, blocks: 4
	for (int i = 0; i < 1; i++) {
		int j;

		unsigned char block_ciphertext[16];
		unsigned char block_plaintext[16];

		int fullblock = ((plaintext_size - (16 * i)) / 16);

		int block_size = fullblock ? 16 : (plaintext_size - (i * 16));
		int padding = 16 - block_size;

		for (j = 0; j < block_size; j++) {
			block_plaintext[j] = plaintext[(16 * i) + j];
		}

		aes_decrypt(block_plaintext, key, block_ciphertext);

		// for (int l = 0; l < 16; l++) {
		// 	ciphertext[l + (i * 16)] = block_ciphertext[l];
		// }
	}


	FILE *encrypted;

	encrypted = fopen("clear", "w+");

	fwrite(ciphertext, sizeof(ciphertext), 1, encrypted);

	fclose(encrypted);

	return 0;
}
