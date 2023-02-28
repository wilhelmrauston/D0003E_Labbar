#include <avr/io.h>
#include <stdbool.h>

#include "TinyTimber.h"
#include "Gui.h"
#include "PulseGen.h"
#include "InputHandler.h"

#define PNE2 (PINE & (1<<PINE2))
#define PNE3 (PINE & (1<<PINE3))
#define PNB4 (PINB & (1<<PINB4))
#define PNB6 (PINB & (1<<PINB6))
#define PNB7 (PINB & (1<<PINB7))


void initialize (CONTROLLER *self) {
    SYNC(self->gui[0], initLCD, 0);
    SYNC(self->ArrPulse[0], generatePulse , NULL);
    ASYNC(self->ArrPulse[1], generatePulse , NULL);
	ASYNC(self->gui[0], printAt, 1);
	ASYNC(self->gui[1], printAt, 1);
	ASYNC(self->gui[0], switchActive, NULL);
}

void movevertical (CONTROLLER *self) {
	
	//PUSH
	if(!(PNB4)) {
		if (self->ArrPulse[self->active]->freq > 0) {
			self->ArrPulse[self->active]->prev = self->ArrPulse[self->active]->freq;
			self->ArrPulse[self->active]->freq = 0;
		}
		else {
			self->ArrPulse[self->active]->freq = self->ArrPulse[self->active]->prev;
            ASYNC(self->ArrPulse[self->active], generatePulse, self->ArrPulse[self->active]->freq);
		}
		ASYNC(self->gui[self->active], printAt, self->ArrPulse[self->active]->freq);
	}

    //UP
    if(!PNB6){
        if (self->ArrPulse[self->active]->freq < 99){
            if (self->ArrPulse[self->active]->freq == 0) {
                ASYNC(self->ArrPulse[self->active], generatePulse, 1);
			}
            self->ArrPulse[self->active]->freq += 1;
            ASYNC(self->gui[self->active], printAt, self->ArrPulse[self->active]->freq);
            AFTER(MSEC(1000), self->ArrPulse[self->active], smoothIncrement, 0);

        }
    }
    //DOWN
    if(!PNB7){
        if (self->ArrPulse[self->active]->freq > 0){
            self->ArrPulse[self->active]->freq -= 1;
            ASYNC(self->gui[self->active], printAt, self->ArrPulse[self->active]->freq);
            AFTER(MSEC(1000), self->ArrPulse[self->active], smoothIncrement, 0);

        }
    }
}

void movehorizontal(CONTROLLER *self) {
	
	//LEFT
	if(!PNE2) {
		if (self->active > 0) {
			ASYNC(self->gui[self->active], switchActive, NULL);
			self->active -= 1;
			ASYNC(self->gui[self->active], switchActive, NULL);
		}
	}
		
	//RIGHT
	else if(!PNE3) {
		if (self->active < 1) {
			ASYNC(self->gui[self->active], switchActive, NULL);
			self->active += 1;
			ASYNC(self->gui[self->active], switchActive, NULL);
		}
	}
}


