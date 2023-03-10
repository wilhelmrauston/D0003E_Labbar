#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "TrafficLight.h"
#include "Gui.h"
#include <stdint.h>

void setLamp (TrafficLight *self, int newActive) {
	SYNC(self->lightGui, switchActive, newActive);
    self->act = newActive;
}

int getLamp(TrafficLight *self) {
	return self->act;
}