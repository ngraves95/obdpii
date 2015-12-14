#include "obdii.h"

const struct pid_entry pid_data[N_PID] = {
	#include "struct_data.txt"
};
