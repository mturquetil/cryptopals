#include <stdio.h>
#include <stdlib.h>

int main () {
	char key[] = "Terminator X: Bring the noise";
	int keysize = sizeof(key) - 1;
	int curr = 0;
	int line_len = 0;
	size_t buffersize = 2900;
	char secret[2900];
	char * line;

	line = malloc(buffersize);

	FILE *file;

	int i = 0, j = 0;
	file = fopen("challenge", "r");

	// get keysize
	while ((line_len = getline(&line, &buffersize, file)) != -1) {
		for (i = 0; i < line_len; i++) {
			if (curr == keysize) {
				curr = 0;
			} 
			
			// printf("%x ^ %c = %c\n", line[i], key[curr], line[i] ^ key[curr]);
			secret[j++] = line[i] ^ key[curr++];
			printf("%d ", secret[j-1]);
		}
	}

	secret[j] = '\0';

	printf("%s", secret);

	fclose(file);
	free(line);

	return 0;
}
