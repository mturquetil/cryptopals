#include <stdio.h>
/* Multiply two numbers in the GF(2^8) finite field defined
 * by the polynomial x^8 + x^4 + x^3 + x + 1 = 0
 * using the Russian Peasant Multiplication algorithm
 * (the other way being to do carry-less multiplication followed by a modular reduction)
 */
int gmul(int a, int b) {
	int p = 0; /* the product of the multiplication */
	while (a && b) {
            if (b & 1) /* if b is odd, then add the corresponding a to p (final product = sum of all a's corresponding to odd b's) */
                p ^= a; /* since we're in GF(2^m), addition is an XOR */

            if (a & 0x80) /* GF modulo: if a >= 128, then it will overflow when shifted left, so reduce */
                a = (a << 1) ^ 0x11b; /* XOR with the primitive polynomial x^8 + x^4 + x^3 + x + 1 (0b1_0001_1011) – you can change it but it must be irreducible */
            else
                a <<= 1; /* equivalent to a*2 */
            b >>= 1; /* equivalent to b // 2 */
	}
	return p;
}

int main () {
	printf("to 33 to : %x\n", (gmul(0x02, 0x33) ^ gmul(0x03, 0x8b) ^ gmul(0x01, 0x76) ^ gmul(0x01, 0x20)));
	printf("to b6 to : %x\n", (gmul(14, 0xb6) ^ gmul(11, 0x84) ^ gmul(13, 0x34) ^ gmul(9, 0xe8)));
}
