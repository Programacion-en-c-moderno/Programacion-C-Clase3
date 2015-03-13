#include <stdio.h>
#include <stdlib.h>

void genera_mensaje(FILE *file)
{
	int linea = 0;

	while (linea < 6) {
		fprintf(file, "Linea %d: Mensaje de prueba\n", linea);
		linea++;
	}
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
		printf("%s", code);
	}

	free(code);
	return 0;
}
