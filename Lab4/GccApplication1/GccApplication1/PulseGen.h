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
} PulseGen;

#define initPulseGen(pin) {initObject(), pin, 1, 0, NULL, NULL}

void generatePulse(PulseGen *self);

void smoothIncrement(PulseGen *self);

#endif