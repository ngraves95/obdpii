#ifndef OBDII_READER_H
#define OBDII_READER_H

#include "obdii.h"

/*
 * Sends a request to the OBD II for the given PID.
 * The output from the request will be put in the out_buffer.
 *
 * Returns:
 *     OBDII_SUCCESS or OBDII_FAILURE
 */
obdii_result_t obdii_read_request(const char pid, OUT char * out_buffer, const int out_buffer_len);


#endif
