#ifndef OBDII_H
#define OBDII_H

typedef enum {
	OBDII_FAILURE,
	OBDII_SUCCESS
} obdii_result_t;

struct pid_entry {
	char pid;
	char response_len;
	char * msg;
};

#define N_PID 0x80

/*
 * Maps each PID to the number of bytes it returns.
 */
extern const struct pid_entry pid_data[N_PID];

/*
 * Use to designate out-parameters.
 */
#define OUT


#endif
