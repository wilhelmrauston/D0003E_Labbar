
#include "TrafficLight.h"


void setLamp (TrafficLight *self, int newActive) {
	SYNC(self->lightGui, switchActive, newActive);
    self->act = newActive;
    switch (self->dir) {
        case 1:
            SYNC(self->wrt, updateNorth, newActive);
			break;
		case -1:
			SYNC(self->wrt, updateSouth, newActive);
			break;
	}
}

int getLamp(TrafficLight *self) {
	return self->act;
}