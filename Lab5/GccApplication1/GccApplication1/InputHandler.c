/*
Bit 0: Northbound car arrival sensor activated
Bit 1: Northbound bridge entry sensor activated
Bit 2: Southbound car arrival sensor activated
Bit 3: Southbound bridge entry sensor activated
*/


void readObserver(InputHandler *self){
	
	char RecievedData = UDR0; // Get data from simulator

	#define NORTHBOUND_ARRIVE	RecievedData & (1 << 0)
	#define NORTHBOUND_ENTRY	RecievedData & (1 << 1)
	#define SOUTHBOUND_ARRIVE	RecievedData & (1 << 2)
	#define SOUTHBOUND_ENTRY	RecievedData & (1 << 3)


	
	if (NORTHBOUND_ARRIVE)	{ ASYNC(self->state,   carArrived      , -1); }
	if (NORTHBOUND_ENTRY)   { ASYNC(self->state,   startCrossing   , -1); }		
	if (SOUTHBOUND_ARRIVE)	{ ASYNC(self->state,   carArrived      , 1); }
	if (SOUTHBOUND_ENTRY)   { ASYNC(self->state,   startCrossing   , 1); }
}