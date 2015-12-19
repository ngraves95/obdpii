#include <stdio.h>
#include <stdlib.h>

#include "obdii.h"
#include "obdii_simple.h"

int main(int argc, char ** argv)
{
	char pids[argc - 1];
	int i;

	if (argc <= 1) {
		printf("{}\n");
		return 0;
	}

	for (i = 1; i < argc; i++) {
		pids[i - 1] = (char)(atoi(argv[i]) & 0xFF);
	}

	obdii_simple_get_response(pids, argc - 1);
	return 0;
}
