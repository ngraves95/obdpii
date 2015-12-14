#include <stdio.h>
#include "obdii.h"

int main(void)
{
	int i;
	for (i = 0; i < N_PID; i++) {
		printf("%u %u %s\n",
		       pid_data[i].pid,
		       pid_data[i].response_len,
		       pid_data[i].msg);
	}

	return 0;
}
