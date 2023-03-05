#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "Gui.h"
#include <stdint.h>

void setLamp (TrafficLight *self, bool newActive) {
    self->active = newActive;
}