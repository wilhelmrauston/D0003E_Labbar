#include "Writer.h"

void sendChar(Writer *self) {
	while(!(UCSR0A & (1 << UDRE0)));
     uint8_t message;
	 if (self->nAct == 1 && self->sAct == 0){
			message = 0b1001;
	 } else if (self->nAct == 0 && self->sAct == 1) {
			message = 0b0110;
	 } else if(self->nAct == 0 && self->sAct == 0) {
			message = 0b1010;
	 } else {
			message = 0b0000;
		
	 }
	UDR0 = message;
}

void getChar(Writer *self) {
	while (!(UCSR0A & (1 << RXC0)));
	char RecievedData = UDR0; // Get data from simulator
		
	return RecievedData;
}

void updateNorth(Writer *self, int newAct) {
    self->nAct = newAct;
	sendChar(self);
}

void updateSouth(Writer *self, int newAct){
    self->sAct = newAct;
	sendChar(self);
}
