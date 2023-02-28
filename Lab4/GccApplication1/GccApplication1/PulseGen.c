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
    if (self->freq > 0) {
        ASYNC(self->PS, sendPulse, self->pin);
        AFTER(MSEC(1000/(self->freq*2)), self, generatePulse, NULL);
    } else {
        ASYNC(self->PS, resetPin, self->pin);
    }
}


void smoothIncrement(PulseGen *self){
    if (!PNB6 && self->freq < 99){
        self->freq += 1;
        ASYNC(self->gui, printAt, self->freq);
		if (!PNB6) {
			AFTER(MSEC(75), self, smoothIncrement, 0);
		}
    }
    if (!PNB7 && self->freq > 0){
        self->freq -= 1;
        ASYNC(self->gui, printAt, self->freq);
        AFTER(MSEC(75), self, smoothIncrement, 0);
    }
}