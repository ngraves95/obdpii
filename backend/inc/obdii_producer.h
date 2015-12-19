#ifndef OBDII_PRODUCER_H
#define OBDII_PRODUCER_H

#include "obdii.h"

/*
 * Makes a request to the OBD-II interface for the given MODE and PID.
 * Returns:
 *     - whether or not the request succeeded.
 */
obdii_result_t obdii_request(char mode, char pid);


#endif
