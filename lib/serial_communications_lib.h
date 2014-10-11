/*
 * serial_communications_lib.h
 *
 *  Created on: 11.10.2014
 *      Author: scheik
 */

#ifndef SERIAL_COMMUNICATIONS_LIB_H_
#define SERIAL_COMMUNICATIONS_LIB_H_

extern "C" void writeBytes(int descriptor, int count);
extern "C" void readBytes(int descriptor, int count);
extern "C" int  openSerialPort (const char * device, int bps);

extern struct termios orig;
extern int filedesc;
extern int fd;
extern unsigned char serialBuffer[16];						// Serial buffer to store data for I/O

#endif /* SERIAL_COMMUNICATIONS_LIB_H_ */
