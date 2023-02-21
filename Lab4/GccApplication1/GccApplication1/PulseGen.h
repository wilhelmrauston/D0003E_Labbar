#ifndef _PULSEGEN_
#define _PULSEGEN_

#include <stdbool.h>
#include <stdint.h>
#include "PulseSender.h"
#include "TinyTimber.h"

typedef struct PulseGen{
    Object super;
    bool active;
    uint8_t pin;
    uint16_t freq;
    PulseSender* PS;

} PulseGen;

#define initPulseGen(active, pin, freq) {initObject(), active, pin, freq}

void generatePulse(PulseGen *self);

#endif