#include "PulseGen.h"
#include <stdbool.h>
#include <stdint.h>


void generatePulse(PulseGen *self) {
    if (self->freq > 0) {
        ASYNC(self->PS, sendPulse, self->pin);
        SEND(SEC(1/self->freq), SEC(2*(1/self->freq)), self, generatePulse, self);
    }

}
