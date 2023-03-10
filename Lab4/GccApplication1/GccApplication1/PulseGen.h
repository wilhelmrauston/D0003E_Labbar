#ifndef _PULSEGEN_
#define _PULSEGEN_

#include <stdbool.h>
#include <stdint.h>
#include "PulseSender.h"
#include "TinyTimber.h"

typedef struct {
    Object super;
    uint8_t pin;
    uint8_t freq;
    uint8_t prev;
    PulseSender *PS;
    GUI *gui;
    bool runNext;
} PulseGen;

#define initPulseGen(pin) {initObject(), pin, 1, 0, NULL, NULL, true}

void generatePulse(PulseGen *self);

void smoothIncrement(PulseGen *self);

uint8_t getFrequency(PulseGen *self);

void setFrequency(PulseGen *self, int newfreq);

uint8_t getPrev(PulseGen *self);

void setPrev(PulseGen *self, int newPrev);



#endif