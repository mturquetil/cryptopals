#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const unsigned char base64_table[65] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

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

int main(int argc, char *argv[]) {
	unsigned char hex[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	unsigned char result[strlen(hex) / 2];

	int j = 0;

	for (int i = 0; i < strlen(hex); i += 2) {
		int f1 = hex2decimal(hex, i);
		int f2 = hex2decimal(hex, i + 1);

		result[j++] = f1 * 16 + f2;
	}

	result[j++] = '\0';

	unsigned char *src = result;
	int len = strlen((char *)src);

	unsigned char encoded[len * 4 / 3 + 4];
	unsigned char *end, *input, *cursor = encoded;

	end = src + len;
	input = src;

	while (end - input >= 3) {
		*cursor++ = base64_table[input[0] >> 2];
		*cursor++ = base64_table[(input[0] & 0x03) << 4 | input[1] >> 4];
		*cursor++ = base64_table[(input[1] & 0x0f) << 2 | input[2] >> 6];
		*cursor++ = base64_table[input[2] & 0x3f];

		input += 3;
	}

	if (end - input) {
		*cursor++ = base64_table[input[0] >> 2];

		if (end - input == 1) {
			*cursor++ = base64_table[(input[0] & 0x03) << 4];
			*cursor++ = '=';
		} else {
			*cursor++ = base64_table[(input[0] & 0x03) << 4 | input[1] >> 4];
			*cursor++ = base64_table[(input[1] & 0x0f) << 2];
		}

		*cursor++ = '=';
	}

	*cursor++ = '\n';
	*cursor++ = '\0';

	printf("\n encoded: %s \n", encoded);

	return 0;
}
