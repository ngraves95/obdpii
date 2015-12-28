#ifndef OBDII_SIMPLE_H
#define OBDII_SIMPLE_H

/*
 * Assumes mode 01.
 */
void obdii_simple_get_response(char * pid_arr, int n_pids);

#endif
