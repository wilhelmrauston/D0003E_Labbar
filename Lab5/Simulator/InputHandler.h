#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_


#include "SerialPort.h"
#include <stdio.h>
#include <stdbool.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

void* input(void *arg);

#endif