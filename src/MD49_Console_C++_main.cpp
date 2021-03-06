//============================================================================
// Name        : cpp_test.cpp
// Author      : scheik
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>   								/* Standard input/output definitions */
#include <stdlib.h>  								/* exit */
#include <string.h>  								/* String function definitions */
#include <unistd.h>  								/* UNIX standard function definitions */
#include <fcntl.h>  	 							/* File control definitions */
#include <errno.h>   								/* Error number definitions */
#include <termios.h> 								/* POSIX terminal control definitions */
#include <ctype.h>   								/* isxxx() */
#include "serial_communications_lib.h"				// serial communications library

using namespace std;

void set_MD49_Commands (void);
void print_help(void);
void parse_input (void);

unsigned char set_Speed1=128;
unsigned char set_Speed2=128;
unsigned char set_Acceleration=5;
unsigned char set_Mode=0;
unsigned char set_Reset=0;
unsigned char set_Regulator=1;
unsigned char set_Timeout=0;
unsigned char set_Encoder1Byte1=0;
unsigned char set_Encoder1Byte2=0;
unsigned char set_Encoder1Byte3=0;
unsigned char set_Encoder1Byte4=0;
unsigned char set_Encoder2Byte1=0;
unsigned char set_Encoder2Byte2=0;
unsigned char set_Encoder2Byte3=0;
unsigned char set_Encoder2Byte4=0;										// speichert eingegebene Kommandos
char input;

int getch()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);           // save old settings
  newt = oldt;
  newt.c_lflag &= ~(ICANON);                 // disable buffering
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);  // apply new settings

  int c = getchar();  // read character (non-blocking)

  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);  // restore old settings
  return c;
}

int main(int argc, char **argv){
	filedesc = openSerialPort("/dev/ttyAMA0", B38400);
	if (filedesc == -1) exit(1);										// Sleep for UART to power up and set options
	printf("MD49_Console started \n");
	print_help();
	while(1){
		//read_MD49_Data();
		input = getch();						// call  non-blocking input function
		//scanf("%s",&input);
		parse_input();

		if (input==113){								// "q" = quit programm
			printf("\n");
			close(fd);									// Close port
			return 0;									// exit
		}
	}//end.mainloop
}//end.mainfunction

void parse_input (void){
	if (input==119){								// input="w" = Full Forward
		print_help();
		set_Speed1=255;
		set_Speed2=255;
		set_MD49_Commands();
	}
	if (input==120){								// "x" = Stop
		print_help();
		set_Speed1=128;
		set_Speed2=128;
		set_MD49_Commands();
	}
	if (input==97){									// "a" = Full Left
		print_help();
		set_Speed1=0;
		set_Speed2=255;
		set_MD49_Commands();
	}
	if (input==100){								// "d" = Full Right
		print_help();
		set_Speed1=255;
		set_Speed2=0;
		set_MD49_Commands();
	}
	if (input==115){								// "s" = Full Backward
		print_help();
		set_Speed1=0;
		set_Speed2=0;
		set_MD49_Commands();
	}
}

void print_help(void){
	printf("\033[2J");        /*  clear the screen  */
	printf("\033[H");         /*  position cursor at top-left corner */
	printf("---------------------------------------------------------- \n");
	printf("Enter 'w', 'a', 's', 'd'\n");
	printf("to drive forward, left, right, backward full speed. \n");
	printf("Enter 'x' to stop drives \n");
	printf("---------------------------------------------------------- \n");
	printf("Enter 'q' to quit program \n");
	printf("---------------------------------------------------------- \n");
	printf("Press a key...:");
}

void set_MD49_Commands (void){
	serialBuffer[0] = 84;							// 84=T Steuerbyte um alle Commands an MD49 zu senden
	serialBuffer[1] = set_Speed1;					// speed1
	serialBuffer[2] = set_Speed2;					// speed2
	serialBuffer[3] = set_Acceleration;				// Acceleration
	serialBuffer[4] = set_Mode;						// Mode
	serialBuffer[5] = set_Reset;					// reset
	serialBuffer[6] = set_Regulator;				// Regulator
	serialBuffer[7] = set_Timeout;					// Timeout
	serialBuffer[8] = set_Encoder1Byte1;
	serialBuffer[9] = set_Encoder1Byte2;
	serialBuffer[10] = set_Encoder1Byte3;
	serialBuffer[11] = set_Encoder1Byte4;
	serialBuffer[12] = set_Encoder2Byte1;
	serialBuffer[13] = set_Encoder2Byte2;
	serialBuffer[14] = set_Encoder2Byte3;
	serialBuffer[15] = set_Encoder2Byte4;
	writeBytes(fd, 16);
}
