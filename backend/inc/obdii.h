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

/*
 * Only 1 OBD-II device may be open at a time,
 * as a car only has 1 OBD-II port.
 */
obdii_result_t obdii_open(char * location);
obdii_result_t obdii_close(void);

#endif
