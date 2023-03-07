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

#define FOSC 8000000UL // Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

int main(void)
{
    Utility utility = initUtility();
    initUtil(&utility, MYUBRR);
    Gui gui[] = {initGui(0), initGui(2), initGui(4)};
    State state = initState();
    state.gui[0] = &gui[0];
    state.gui[1] = &gui[1];
    state.gui[2] = &gui[2];
    while (1) 
    {
        INSTALL(&state, receivedInterrut, IRQ_USART0_RX);
        TINYTIMBER(&state, initialize, NULL);   
    }
}

