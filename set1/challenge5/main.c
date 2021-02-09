#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char frequent_char[] = { 'e', 't', 'a', 'o', 'i', 0 };

typedef struct {
	char c;
	int count;
} char_freq;

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

void r_xor_encrypt(char * str, int strsize, char * key, int keysize) {
	int key_count = 0;
	char encrypted[strsize];

	for (int i = 0; i < strsize - 1; i++) {
		encrypted[i] = str[i] ^ key[key_count++];

		if (key_count == keysize - 1) {
			key_count = 0;
		}
		printf("%02x", encrypted[i]);
	}
}

int main () {
 	char plaintext[] = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
 	char key[] = "ICE";

 	r_xor_encrypt(plaintext, sizeof(plaintext), key, sizeof(key));
}
