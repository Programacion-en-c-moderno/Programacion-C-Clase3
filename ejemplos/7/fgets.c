#include <stdio.h>
#include <stdlib.h>

void genera_mensaje(FILE *file)
{
	fputs("El mensaje a escribir es Alvaro", file);
	rewind(file);
}

int main (void)
{
	FILE *file = fopen("datos.dat", "a+");
	char *code;
	size_t n = 0;
	int c;

	if (file == NULL)
		return -1;

	genera_mensaje(file);

	code = malloc(101);
	while(fgets(code, 100, file)) {
		printf("%s\n", code);
	}

	free(code);
	return 0;
}
