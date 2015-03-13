#include <stdio.h>
#include <stdlib.h>

void genera_mensaje(FILE *file)
{
	fputc('A', file);
	fputc('l', file);
	fputc('v', file);
	fputc('a', file);
	fputc('r', file);
	fputc('o', file);
	rewind(file);
}

int main(void)
{
	FILE *file = fopen("datos.dat", "a+");
	char *code;
	size_t n = 0;
	int c;

	if (file == NULL)
		return -1;

	genera_mensaje(file);

	code = malloc(1000);
	while ((c = fgetc(file)) != EOF)
	{
		code[n++] = (char) c;
	}

	code[n] = '\0';
	printf("El texto leido es %s\n", code);

	free(code);
	return 0;
}
