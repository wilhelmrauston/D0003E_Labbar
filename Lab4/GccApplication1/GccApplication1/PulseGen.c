#include <stdbool.h>
#include <stdint.h>
#include <avr/io.h>
#include "PulseGen.h"
#include "PulseSender.h"
#include "TinyTimber.h"
#include "Gui.h"

#define PNE2 (PINE & (1<<PINE2))
#define PNE3 (PINE & (1<<PINE3))
#define PNB4 (PINB & (1<<PINB4))
#define PNB6 (PINB & (1<<PINB6))
#define PNB7 (PINB & (1<<PINB7))

void generatePulse(PulseGen *self) {	
	uint8_t frq = self->freq;
	if (frq > 0) {
		ASYNC(self->PS, sendPulse, self->pin);
		AFTER(USEC(1000000/(frq*2)), self, generatePulse, NULL);
	} else {
		ASYNC(self->PS, resetPin, self->pin);
		AFTER(MSEC(500), self, generatePulse, NULL);
	}
}


void smoothIncrement(PulseGen *self){
    if (!PNB6 && self->freq < 99){
        self->freq += 1;
        SYNC(self->gui, printAt, self->freq);
		if (!PNB6) {
			AFTER(MSEC(100), self, smoothIncrement, 0);
		}
    }
    if (!PNB7 && self->freq > 0){
        self->freq -= 1;
        SYNC(self->gui, printAt, self->freq);
        AFTER(MSEC(100), self, smoothIncrement, 0);
    }
}

uint8_t getFrequency(PulseGen *self){
    return self->freq;
}

void setFrequency(PulseGen *self, int newfreq){
    self->freq = newfreq;
}

uint8_t getPrev(PulseGen *self) {
    return self->prev;
}

void setPrev(PulseGen *self, int newPrev) {
    self->prev = newPrev;
}