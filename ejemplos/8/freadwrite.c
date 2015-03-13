#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp;
	char c[] = "ejemplo fwrite/fread";
	char buffer[20];

	fp = fopen("datos.dat", "w+");
	if (fp == NULL)
		return -1;

	fwrite(c, strlen(c) + 1, 1, fp);

	rewind(fp);

	fread(buffer, strlen(c) + 1, 1, fp);
	printf("%s\n", buffer);

	fclose(fp);
	return 0;
}
