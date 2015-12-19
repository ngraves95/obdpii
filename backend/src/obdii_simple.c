/*
 * This class is a simple prototype to both read and write from the OBD-II
 * device without any threading.
 */
#include "obdii_consumer.h"
#include "obdii_producer.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/*
 * Used for communication between obdii_request and obdii_read.
 * This only exists for mocking purposes, and can be thought of
 * as the OBD-II device itself.
 */
static char last_pid_requested;

/*
 * Mock requester for now.
 */
obdii_result_t obdii_request(char mode, char pid)
{
	/* Make compiler shutup over unused variables */
	last_pid_requested = pid;
	return (obdii_result_t) mode | 0x1;
}

/*
 * Mock reader for now.
 */
obdii_result_t obdii_read(char * out_buffer, int * bytes_read)
{
	int pid = last_pid_requested;
	int n_bytes = pid_data[pid].response_len;
	int i;
	char mock_data[sizeof(int) / sizeof(char)];

	time_t t;
	srand((unsigned) time(&t));

	for (i = 0; i < sizeof(mock_data) / sizeof(mock_data[0]); i++) {
		mock_data[i] = rand() & 0xFF;
	}

	char * cur = out_buffer;

	cur += sprintf(cur, "%d %x", 41, pid);

	for(i = 0; i < n_bytes && i < (int)sizeof(mock_data); i++) {
		cur += sprintf(cur, " %x", mock_data[i]);
	}

	*cur = '\0';
	*bytes_read = (int)(cur - out_buffer);
	return OBDII_SUCCESS;
}


obdii_result_t obdii_parse(struct pid_response * out, int * n_out,
			   char * src, int src_len)
{
	/*
	 * src should look like:
	 * 41 0A BE 0F 1C
	 */

	/* Grab and NUL-terminate PID. */
	int accum = 0;
	char * tok = strtok(src, " ");
	tok = strtok(NULL, " "); /* Pass over first byte. */
	out->pid = (char) (strtol(tok, NULL, 16) & 0xFF);

	/* Convert payload from string to int */
	while (tok) {
		accum = accum << 8;
		accum |= (int) (strtol(tok, NULL, 16) & 0xFF);
		tok = strtok(NULL, " ");
	}

	out->value = accum;

	return OBDII_SUCCESS;
}

/*
 * Encodes each pid as JSON with the schema:
 *
 * {
 *     "17" : 97;
 * }
 *
 */
char * obdii_encode(char * out_buffer, int len,
			    struct pid_response * pid_arr, int n_pids)
{
	char * current;
	int i;

	if (len <= 0 || out_buffer == NULL) {
		/* Arbitrary memory request. Should fix this. */
		out_buffer = malloc(18 * n_pids + 3);
		if (!out_buffer) {
			return NULL;
		}
	}

	out_buffer[0] = '{';

	for (current = out_buffer + 1, i = 0; i < n_pids; i++) {
		current += sprintf(current, "\"%d\":%d,",
				   pid_arr[i].pid,
				   pid_arr[i].value);
	}

	/* Replace last comma with a closing brace and NUL-terminate. */
	*(current - 1) = '}';
	*current = '\0';

	return out_buffer;
}


/*
 * Prints result to stdout.
 */
obdii_result_t obdii_return(char * src_buf)
{
	printf("%s\n", src_buf);
	return OBDII_SUCCESS;
}

void obdii_simple_get_response(char * pids, int n_pids)
{
	struct pid_response obdii_data[n_pids];
	char read_buffer[50] = { 0 };
	char * encoded = NULL;  /* Points to char buffer.  */
	int used = 50;		/* Out param for bytes read / data parsed */
	int i;

	for (i = 0; i < n_pids; i++) {
		obdii_request(0x01, pids[i]);
		obdii_read(read_buffer, &used);
		obdii_parse(&obdii_data[i], &used, read_buffer, used);
	}

	encoded = obdii_encode(encoded, -1, obdii_data, n_pids);
	obdii_return(encoded);
	free(encoded);
}
