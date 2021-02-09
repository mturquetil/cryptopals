#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hex2decimal (unsigned char hexstring[], int index) {
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

static const unsigned char base64_table[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char *argv[]) {
	unsigned char hex[] = "1c0111001f010100061a024b53535009181c";
	unsigned char toxor[] = "686974207468652062756c6c277320657965";
	
	unsigned char result1[strlen(hex) / 2];
	unsigned char result2[strlen(hex) / 2];

	int j = 0;

	for (int i = 0; i < strlen(hex); i += 2) {
		int f1 = hex2decimal(hex, i);
		int f2 = hex2decimal(hex, i + 1);

		result1[j++] = f1 * 16 + f2;
	}

	j = 0;

	for (int i = 0; i < strlen(hex); i += 2) {
		int f1 = hex2decimal(toxor, i);
		int f2 = hex2decimal(toxor, i + 1);

		result2[j++] = f1 * 16 + f2;
	}

	for (int i = 0; i < strlen(hex) / 2; i++) {
		printf("%x", result1[i]^result2[i]);
	}

	return 0;
}
