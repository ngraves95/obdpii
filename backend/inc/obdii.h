#ifndef OBDII_H
#define OBDII_H

typedef enum {
	OBDII_FAILURE,
	OBDII_SUCCESS
} obdii_result_t;

struct pid_entry {
	char pid;
	char response_len;
	char * msg; /* <REMOVE ME> */
};

struct pid_response {
	char pid;
	int value;
};

#define N_PID 0x80

/*
 * Maps each PID to the number of bytes it returns.
 */
extern const struct pid_entry pid_data[N_PID];

#define OBDII_DEVICE "path/to/device"

#endif
