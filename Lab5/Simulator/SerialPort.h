#ifndef SERIALPORT_H_
#define SERIALPORT_H_	

	
#include <stdint.h>		
#include <termios.h>
#include <fcntl.h>
#include <stdio.h>		
#include <stdlib.h>		
#include <unistd.h>
#include <stdbool.h>
#include "globals.h"
#include <pthread.h>
#include "Simulator.h"



void initSerialPort(void);

void writeToAVR(uint8_t instruction);

void getLights();

#endif

