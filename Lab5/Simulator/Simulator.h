#ifndef SIMULATOR_H_
#define SIMULATOR_H_


#include <stdlib.h>

#include <unistd.h>
#include <pthread.h>
#include "SerialPort.h"


void* startCrossing(void* arg);

void* simulate (void* arg);

#endif

