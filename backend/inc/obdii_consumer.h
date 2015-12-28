#ifndef OBDII_CONSUMER_H
#define OBDII_CONSUMER_H

#include "obdii.h"

/*
 * Reads from FD and stores the result in OUT_BUFFER.
 * the value of BYTES_READ indicates the length of the data returned.
 * This function does no parsing, only transfers data.
 */
obdii_result_t obdii_read(char * out_buffer, int * bytes_read);

/*
 * Parses the raw data into a meaningful format with pid and value.
 * The raw data is read from SRC and stored in OUT. The value of N_OUT
 * indicates how many results were parsed.
 */
obdii_result_t obdii_parse(struct pid_response * out, int * n_out,
			   char * src, int src_len);

/*
 * Reads the data from PID_ARR and returns the formatted data in OUT_BUFFER.
 *
 * If LEN <= 0 or OUT_BUFFER == NULL, then OUT_BUFFER is to be dynamically
 *  allocated. Otherwise, LEN indicates the size of the buffer.
 *
 * N_PIDS indicates the number of
 */
char * obdii_encode(char * out_buffer, int len,
			    struct pid_response * pid_arr, int n_pids);

/*
 * Returns the results of the read to the server. Implementation is not
 * defined; this may be done via stdout, database, etc.
 */
obdii_result_t obdii_return(char * src_buf);

#endif
