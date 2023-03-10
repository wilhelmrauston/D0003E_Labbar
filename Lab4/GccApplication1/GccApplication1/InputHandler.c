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
	ASYNC(self->ArrPulse[0], generatePulse , NULL);
    ASYNC(self->ArrPulse[1], generatePulse , NULL);
	ASYNC(self->gui[0], printAt, 1);
	ASYNC(self->gui[1], printAt, 1);
	ASYNC(self->gui[0], switchActive, NULL);
}

void movevertical (CONTROLLER *self) {
	uint8_t ac = self->active;
	uint8_t frq =  SYNC(self->ArrPulse[ac], getFrequency, NULL);
	//PUSH
	if(!(PNB4)) {
		if (self->debounce == 0) {
			self->debounce = 1;
			uint8_t prv = SYNC(self->ArrPulse[ac], getPrev, NULL);
			if (frq > 0) {
				SYNC(self->ArrPulse[ac], setPrev, frq);
				SYNC(self->ArrPulse[ac], setFrequency, 0);
				SYNC(self->gui[ac], printAt, 0);
			}
			else {
				SYNC(self->ArrPulse[ac], setFrequency, prv);
				SYNC(self->gui[ac], printAt, prv);
			}
			AFTER(MSEC(200), self, resetDebounce, NULL);
		}
	}

    //UP
    if(!PNB6){
		if (self->debounce == 0) {
			self->debounce = 1;
			if (frq < 99){
				self->holding = AFTER(MSEC(1000), self->ArrPulse[ac], smoothIncrement, 0);
				ASYNC(self->ArrPulse[ac], setFrequency, frq + 1);
				SYNC(self->gui[ac], printAt, frq + 1);

			}
			AFTER(MSEC(200), self, resetDebounce, NULL);
		}
    }
    //DOWN
    if(!PNB7){
		if (self->debounce == 0) {
			self->debounce = 1;
			if (frq > 0) {
				ASYNC(self->ArrPulse[ac], setFrequency, frq - 1);
				SYNC(self->gui[ac], printAt, frq - 1);
				self->holding = AFTER(MSEC(1000), self->ArrPulse[ac], smoothIncrement, 0);

			}
			AFTER(MSEC(200), self, resetDebounce, NULL);
		}
    }
	
	//RELEASE DOWN OR UP
	if (PNB7 && PNB6) {
		if (self->holding) {
			ABORT(self->holding);
			self->holding = NULL;
		}
	}
}

void movehorizontal(CONTROLLER *self) {
	
	//LEFT
	if(!PNE2) {
		if (self->debounce == 0) {
			self->debounce = 1;
			if (self->active > 0) {
				SYNC(self->gui[self->active], switchActive, NULL);
				self->active -= 1;
				SYNC(self->gui[self->active], switchActive, NULL);
			}
		}
		AFTER(MSEC(200), self, resetDebounce, NULL);
	}
		
	//RIGHT
	else if(!PNE3) {
		if (self->debounce == 0) {
			self->debounce = 1;
			if (self->active < 1) {
				SYNC(self->gui[self->active], switchActive, NULL);
				self->active += 1;
				SYNC(self->gui[self->active], switchActive, NULL);
			}
		AFTER(MSEC(200), self, resetDebounce, NULL);
		}
	}
}

void resetDebounce(CONTROLLER *self) {
	self->debounce = 0;
}
