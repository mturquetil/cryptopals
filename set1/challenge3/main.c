#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void hex2decimal (char hexstring[], char * result) {
	for (int i = 0; i < strlen(hexstring); i += 2) {
		int f1 = get_decimal(hexstring, i);
		int f2 = get_decimal(hexstring, i + 1);

		*result++ = f1 * 16 + f2;
	}

	*result++ = '\0';
}

int main(int argc, char *argv[]) {
	char hex[] = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	char result[strlen((const char*)hex) / 2];
	char secret[strlen((const char*)hex) / 2];
	char xor_char;

	hex2decimal(hex, result);

	char frequent[] = { 'e', 't', 'a', 'o', 'i', 0 };
	char hex_frequent[] = { 120, 55, 0 };

	for (int i = 0; i < strlen(hex_frequent); i++) {
		for (int j = 0; j < strlen(frequent); j++) {
			xor_char = hex_frequent[i] ^ frequent[j];

			for (int k = 0; k < strlen(result); k++) {
				secret[k] = result[k] ^ xor_char;
			}

			printf("xor_char %x, secret: %s \n", xor_char, secret);
		}
	}

	return 0;
}
