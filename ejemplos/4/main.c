#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[])
{
	int val, option_index = 0;
	static struct option long_options[] = {
		{ "display", required_argument, 0, 'd' },
		{ "update", required_argument, 0, 'u' },
		{ "force", required_argument, 0, 'f' },
		{ 0 }
	};

	val = getopt_long(argc, argv, "d:u:f:", long_options, &option_index);
	if (val == -1)
		return val;

	switch (val) {
	case 'd':
		printf("Opcion d\n");
		break;
	case 'u':
		printf("Opcion u\n");
		break;
	case 'f':
		printf("Opcion f\n");
		break;
	default:
		printf("Debe usar el parametro -d/-display, -f/-force"
		       "o -u/-update\n");
		break;
	}

	return 0;
}
