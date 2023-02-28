#include "PulseSender.h"
#include <avr/io.h>
#include <stdint.h>

void sendPulse(PulseSender *self, uint8_t pin){

    //Invert bit at position pin
    PORTE ^= 0x1 << pin;
}   

void resetPin(PulseSender *self, uint8_t pin) {
    PORTE &= ~(0x1 << pin);
}