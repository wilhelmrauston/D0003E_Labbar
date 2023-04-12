#ifndef WRITER_H
#define WRITER_H

#include <avr/io.h>
#include "TinyTimber.h"
#include <avr/interrupt.h>
#include <stdbool.h>


typedef struct Writer {
    Object super;
    int sAct;
    int nAct;
} Writer;

#define initWriter() {initObject(), 0, 0}

void sendChar(Writer *self);


void updateNorth(Writer *self, int newAct);

void updateSouth(Writer *self, int newAct);

void getChar(Writer *self);

#endif