#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i;

	if (argc < 2) {
		fprintf(stderr, "Numero de argumentos incompleto\n");
		exit(EXIT_FAILURE);
	}

	if (strcmp(argv[1], "al") == 0)
		printf("hemos recibido \"al\"\n");
	else if (strcmp(argv[1], "va") == 0)
		printf("hemos recibido \"va\"\n");
	else if (strcmp(argv[1], "ro") == 0)
		printf("hemos recibido \"ro\"\n");
	else {
		fprintf(stderr, "Parametro incorrecto\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}
