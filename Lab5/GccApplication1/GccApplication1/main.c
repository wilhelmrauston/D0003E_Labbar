/*
 * GccApplication1.c
 *
 * Created: 2023-02-28 13:25:58
 * Author : Nils
 */ 

#include <avr/io.h>
#include "TinyTimber.h"
#include "Gui.h"
#include "State.h"
#include "Utility.h"
#include "InputHandler.h"
#include "TrafficLight.h"
#include "Writer.h"

#define FOSC 8000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1


Utility utility = initUtility();
Gui gui[] = {initGui(0), initGui(2), initGui(4)};
State state = initState();
InputHandler inputHandler = initInputHandler(); 
TrafficLight NL = initTrafficLight(0, 1);
TrafficLight SL = initTrafficLight(0, -1);
Writer writer = initWriter();


int main(void)
{
	initUtil(&utility, MYUBRR);
	inputHandler.state = &state;
	inputHandler.wrt = &writer;
	state.gui[0] = &gui[0];
	state.gui[1] = &gui[1];
	state.gui[2] = &gui[2];
	SL.lightGui = &gui[0]; 
	NL.lightGui = &gui[2];
    SL.wrt = &writer;
    NL.wrt = &writer;
	state.northLight = &NL;
	state.southLight = &SL;
    INSTALL(&inputHandler, readObserver, IRQ_USART0_RX);
    return TINYTIMBER(&state, initialize, NULL);
}

