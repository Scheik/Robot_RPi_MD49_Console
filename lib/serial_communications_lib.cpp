/*
 * serial_communications_lib.cpp
 *
 *  Created on: 11.10.2014
 *      Author: scheik
 */
#include <iostream>
#include <stdio.h>   /* Standard input/output definitions */
#include <stdlib.h>  /* exit */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <ctype.h>   /* isxxx() */
#include "serial_communications_lib.h"

using namespace std;

struct termios orig;
int filedesc;
int fd;
unsigned char serialBuffer[18];						// Serial buffer to store data for I/O

int openSerialPort(const char * device, int bps)
{
   struct termios neu;
   char buf[128];

   fd = open(device, O_RDWR | O_NOCTTY);

   if (fd == -1)
   {
      sprintf(buf, "openSerialPort %s error", device);
      perror(buf);
   }
   else
   {
      tcgetattr(fd, &orig); 						/* save current serial settings */
      tcgetattr(fd, &neu);
      cfmakeraw(&neu);
      //fprintf(stderr, "speed=%d\n", bps);
      cfsetispeed(&neu, bps);
      cfsetospeed(&neu, bps);
      tcsetattr(fd, TCSANOW, &neu); 				/* set new serial settings */
      fcntl (fd, F_SETFL, O_RDWR);
   }
   return fd;
}

void writeBytes(int descriptor, int count) {
	if ((write(descriptor, serialBuffer, count)) == -1) {	// Send data out
		perror("Error writing");
		close(descriptor);				// Close port if there is an error
		exit(1);
	}
	//write(fd,serialBuffer, count);

}

void readBytes(int descriptor, int count) {
	if (read(descriptor, serialBuffer, count) == -1) {	// Read back data into buf[]
		perror("Error reading ");
		close(descriptor);				// Close port if there is an error
		exit(1);
	}
}
