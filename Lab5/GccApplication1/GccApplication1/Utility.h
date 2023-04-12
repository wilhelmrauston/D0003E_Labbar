#ifndef UTILITY_H
#define UTILITY_H

#include <avr/io.h>
#include "TinyTimber.h"

typedef struct Utility{
	Object super;
} Utility;

#define initUtility() {initObject()}

void initUtil(Utility *self, unsigned int ubrr);


#endif