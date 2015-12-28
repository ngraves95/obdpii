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

#include <errno.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>

#define LOCATION "/dev/"
#define NAME "ttyUSB0"
#define DEVICE_NAME (LOCATION NAME)

#ifdef DEBUG
#define DEBUG_DETAIL(msg, payload) fprintf(stderr, "[%s] %s %s\n",\
					   __func__, msg, payload)
#define DEBUG_PRINT(msg) fprintf(stderr, "[%s] %s\n", __func__, msg)
#define DEBUG_CODE(msg) fprintf(stderr, "[%s] Error code: %d\n",\
				__func__, msg)
#else
#define DEBUG_DETAIL(msg, payload)
#define DEBUG_PRINT(msg)
#define DEBUG_CODE(msg)
#endif

/*
 * The file descriptor from opening DEVICE_NAME.
 *
 * If file_des == 0, aka stdout, then we know the file descriptor
 * for DEVICE_NAME has not been opened yet, and we need to.
 */
static int file_des = 0;

/*
 * Device configuration. OBD-II reader should be:
 * <BAUD>-8-N-1.
 * Important: use the constants defines in termios.h
 * Large amounts of code taken from:
 * http://stackoverflow.com/questions/6947413/how-to-open-read-and-write-from-serial-port-in-c
 */
static int configure_device(int fd, int baud, int nbits,
			    int parity, int stop_bits)
{
	struct termios tty;
	memset(&tty, 0, sizeof(tty));

	if (tcgetattr(fd, &tty) != 0) {
		DEBUG_PRINT("Failed to get attr (tcgetattr)");
		DEBUG_CODE(errno);
		return -1;
	}

	/* Set baud rate. */
	cfsetospeed(&tty, baud);
	cfsetispeed(&tty, baud);

	/* Set bits per byte */
	tty.c_cflag &= (~CSIZE);
	tty.c_cflag |= nbits;

	/* Set control flags. This code taken directly from SO */
	tty.c_iflag &= ~IGNBRK;         /* disable break processing */
	tty.c_iflag &= ~(IXON | IXOFF | IXANY);  /* shut off xon/xoff ctrl */
        tty.c_lflag = 0;                /* no signaling chars, no echo, */
        tty.c_oflag = 0;

        tty.c_cc[VMIN]  = 0;            /* read doesn't block */
        tty.c_cc[VTIME] = 5;            /* 0.5 seconds read timeout */

        tty.c_cflag |= (CLOCAL | CREAD); /* ignore modem controls, */
                                         /* enable reading */

	/*
	 * Set the parity. The parity argument contains both the
	 * enable flag and, if the parity is enabled, whether the
	 * parity is even or odd.
	 */
	tty.c_cflag &= ~(PARENB | PARODD);
	tty.c_cflag |= parity;

	/* Set the stop bits. Default is 1 stop bit. */
	tty.c_cflag &= ~(CSTOPB);
	tty.c_cflag |= stop_bits;

	tty.c_cflag &= ~(CRTSCTS); /* This was from stack overflow */

	if (tcsetattr(fd, TCSANOW, &tty) != 0) {
		DEBUG_PRINT("Failed to set attr (tcsetattr)");
		DEBUG_CODE(errno);
		return -2;
	}

	return 0;
}

static int set_blocking (int fd, int should_block)
{
        struct termios tty;
        memset (&tty, 0, sizeof(tty));

        if (tcgetattr (fd, &tty) != 0) {
                return - 1;
        }

        tty.c_cc[VMIN]  = !!should_block; /* Coerce to 1 or 0 */
        tty.c_cc[VTIME] = 30;		  /* 3 second timeout */

        if (tcsetattr (fd, TCSANOW, &tty) != 0) {
		return -2;
	}

	return 0;
}

/*
 * Configures the OBD-II device with the default set up:
 *     38400-8-N-1
 * Also set the device to block until the specified number of bytes are
 * are received.
 */
static int configure_obdii(int fd)
{
	/*
	 * Doing the structure like this is a little more verbose,
	 * but more informative on a failure.
	 * Failure codes in [-1, -2] correspond to configure_device.
	 * Failure codes in [-4, -8] correspond to set_blocking.
	 */
	int retval = configure_device(fd, B38400, CS8, 0, 0);
	if (retval != 0) {
		DEBUG_PRINT("Failed to configure device.");
		return retval;
	}

	retval = set_blocking(fd, 0);
	return retval << 2;
}

/*
 * Opens the OBD-II device referenced by the file path.
 */
obdii_result_t obdii_open(char * location)
{
	int temp = open(DEVICE_NAME, O_RDWR | O_NOCTTY | O_SYNC);
	if (temp == -1) {
		return OBDII_FAILURE;
	}

	file_des = temp;
	return (configure_obdii(file_des) == 0)
		? OBDII_SUCCESS : OBDII_FAILURE;
}

/*
 * Closes the OBD-II device that was opened.
 */
obdii_result_t obdii_close(void)
{
	return (close(file_des) == 0) ? OBDII_SUCCESS : OBDII_FAILURE;
}

/*
 * Mock requester for now.
 */
obdii_result_t obdii_request(char mode, char pid)
{
	/*
	 * A write looks like 0100\r\n
	 * write_buf holds an extra char for a null terminator,
	 * which is invaluable for debugging.
	 */
	char write_buf[7];
	char * cur = &write_buf[0];
	unsigned count = sizeof(write_buf) - 1;

	/* Check if we need to open the OBD-II reader. */
	if (file_des == 0) {
		DEBUG_PRINT("Opening device");
		if (obdii_open(DEVICE_NAME) == OBDII_FAILURE) {
			DEBUG_DETAIL("Failed to open", DEVICE_NAME);
			return OBDII_FAILURE;
		}
		DEBUG_PRINT("Device opened");
	}

	cur += sprintf(cur, "%02d%02x\r\n", mode, ((unsigned) pid) & 0xFFU);
	*cur = '\0';

	DEBUG_PRINT("Writing to device.");
	/* Write to device. */
	if (write(file_des, write_buf, count) != count) {
		DEBUG_PRINT("Failed to write enough bytes.");
		DEBUG_DETAIL("Target:", write_buf);
		return OBDII_FAILURE;
	}

	DEBUG_PRINT("Write succeeded.");
	return OBDII_SUCCESS;
}

/*
 * Mock reader for now.
 */
obdii_result_t obdii_read(char * out_buffer, int * bytes_read)
{
        /* Check if we need to open the OBD-II reader. */
	if (file_des == 0) {
		DEBUG_PRINT("Opening device");
		if (obdii_open(DEVICE_NAME) == OBDII_FAILURE) {
			DEBUG_DETAIL("Failed to open", DEVICE_NAME);
			return OBDII_FAILURE;
		}
	}

	DEBUG_PRINT("Reading from device.");

	int target = *bytes_read; /* Maximum we are able to read */
	int nread = 0;
	while (target > 0 && out_buffer[-1] != '>') {
		nread = read(file_des, out_buffer, 1 );
		out_buffer += nread;
		target -= nread;
		DEBUG_DETAIL("Read:", out_buffer - nread);
	}

	*bytes_read -= target;

	return OBDII_SUCCESS;
}

static int is_number_start(char c)
{
	return (c >= '0' && c <= '9') || (c >= 'A' && c <= 'F');
}

obdii_result_t obdii_parse(struct pid_response * out, int * n_out,
			   char * src, int src_len)
{
	/*
	 * src should look like:
	 * 41 0A BE 0F 1C
	 */
	char pid_buf[] = {src[2], src[3], '\0'}; /* Get PID from echo */
	int accum = 0;
	int i = 0;

	char * tok = strtok(src, " ");
	tok = strtok(NULL, " "); /* Pass over first 2 tokens. */
	tok = strtok(NULL, " ");
	/* Convert payload from string to int */
	while (tok && is_number_start(tok[0])) {
		DEBUG_DETAIL("Token parsed:", tok);
		accum |= (int) (strtol(tok, NULL, 16) & 0xFF) << (8 * i);
		i++;
		tok = strtok(NULL, " ");
	}

	out->pid = (char) (strtol(pid_buf, NULL, 16) & 0xFF);
	out->value = pid_formulas[(int)out->pid](accum);

	return OBDII_SUCCESS;
}

/*
 * Encodes each pid as JSON with the schema, e.g:
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
	char * encoded = NULL;  /* Points to char buffer.  */

#ifdef DEBUG
	time_t start, end;
	time(&start);
#endif

	int i;
	for (i = 0; i < n_pids; i++) {
		char read_buffer[50] = { 0 };
		int used = sizeof(read_buffer) / sizeof(read_buffer[0]);

		obdii_request(0x01, pids[i]);
		obdii_read(read_buffer, &used);
		obdii_parse(&obdii_data[i], &used, read_buffer, used);
	}

	encoded = obdii_encode(encoded, -1, obdii_data, n_pids);
	obdii_return(encoded);
	free(encoded);

#ifdef DEBUG
	time(&end);
	fprintf(stderr, "Total execution time: %ld seconds\n", end - start);
#endif
}
