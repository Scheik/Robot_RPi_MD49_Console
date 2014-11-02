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

void read_MD49_Data (void);
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
unsigned char set_Encoder2Byte4=0;
char input;											// speichert eingegebene Kommandos

int main(int argc, char **argv){
   filedesc = openSerialPort("/dev/ttyAMA0", B38400);
   if (filedesc == -1) exit(1);
   usleep(40000);									// Sleep for UART to power up and set options

   printf("MD49_Console started \n");
   print_help();

   while(1){
		printf("Comand:");
		scanf("%s",&input);
		parse_input();
		if (input==113){								// "q" = quit programm
			close(fd);									// Close port
			return 0;									// exit
		}
    }//end.mainloop
}//end.mainfunction

void parse_input (void){
	if (input==119){								// input="w" = Full Forward
		set_Speed1=255;
		set_Speed2=255;
		set_MD49_Commands();
	}
	if (input==120){								// "x" = Stop
		set_Speed1=128;
		set_Speed2=128;
		set_MD49_Commands();
	}
	if (input==97){									// "a" = Full Left
		set_Speed1=0;
		set_Speed2=255;
		set_MD49_Commands();
	}
	if (input==100){								// "d" = Full Right
		set_Speed1=255;
		set_Speed2=0;
		set_MD49_Commands();
	}
	if (input==115){								// "s" = Full Backward
		set_Speed1=0;
		set_Speed2=0;
		set_MD49_Commands();
	}
	if (input==104){								// "h" = print help again
		print_help();
	}
	if (input==82){									// "R" = read MD49data
		read_MD49_Data();
	}
}

void print_help(void){
	printf("---------------------------------------------------------- \n");
	printf("Enter 'w', 'a', 's', 'd'\n");
	printf("to drive forward, left, right, backward full speed. \n");
	printf("Enter 'x' to stop drives \n");
	printf("---------------------------------------------------------- \n");
	printf("Enter 'R' to read complete MD49 Data \n");
	printf("---------------------------------------------------------- \n");
	printf("Enter 'q' to quit program \n");
	printf("Enter 'h' to show instructions again \n");
	printf("---------------------------------------------------------- \n");
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

void read_MD49_Data (void){
	serialBuffer[0] = 82;							// 82=R Steuerbyte um alle Daten vom MD49 zu lesen
	serialBuffer[1] = 0;
	serialBuffer[2] = 0;
	serialBuffer[3] = 0;
	serialBuffer[4] = 0;
	serialBuffer[5] = 0;
	serialBuffer[6] = 0;
	serialBuffer[7] = 0;
	serialBuffer[8] = 0;
	serialBuffer[9] = 0;
	serialBuffer[10] = 0;
	serialBuffer[11] = 0;
	serialBuffer[12] = 0;
	serialBuffer[13] = 0;
	serialBuffer[14] = 0;
	serialBuffer[15] = 0;
	writeBytes(fd, 16);
	//usleep(400000);
	//Daten lesen und in Array schreiben
	readBytes(fd, 18);
	printf("Encoder1 Byte 1: ");
	cout<<serialBuffer[0];
	printf("\n");
	printf("Encoder1 Byte 2: ");
	cout<<serialBuffer[1];
	printf("\n");
	printf("Encoder1 Byte 3: ");
	cout<<serialBuffer[2];
	printf("\n");
	printf("Encoder1 Byte 4: ");
	cout<<serialBuffer[3];
	printf("\n");
	printf("Encoder2 Byte 1: ");
	cout<<serialBuffer[4];
	printf("\n");
	printf("Encoder2 Byte 2: ");
	cout<<serialBuffer[5];
	printf("\n");
	printf("Encoder2 Byte 3: ");
	cout<<serialBuffer[6];
	printf("\n");
	printf("Encoder2 Byte 4: ");
	cout<<serialBuffer[7];
	printf("\n");
	printf("Speed1: ");
	cout<<serialBuffer[8];
	printf("\n");
	printf("Speed2: ");
	cout<<serialBuffer[9];
	printf("\n");
	printf("Volts: ");
	cout<<serialBuffer[10];
	printf("\n");
	printf("Current1: ");
	cout<<serialBuffer[11];
	printf("\n");
	printf("Current2: ");
	cout<<serialBuffer[12];
	printf("\n");
	printf("Error: ");
	cout<<serialBuffer[13];
	printf("\n");
	printf("Acceleration: ");
	cout<<serialBuffer[14];
	printf("\n");
	printf("Mode: ");
	cout<<serialBuffer[15];
	printf("\n");
	printf("Regulator: ");
	cout<<serialBuffer[16];
	printf("\n");
	printf("Timeout: ");
	cout<<serialBuffer[17];
	printf("\n");
}
