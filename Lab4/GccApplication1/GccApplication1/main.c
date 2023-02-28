/*
 * GccApplication1.c
 *
 * Created: 2023-02-14 13:11:34
 * Author : Nils
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include "Gui.h"
#include "InputHandler.h"
#include "PulseGen.h"
#include "PulseSender.h"
#include "TinyTimber.h"


PulseSender PS = initPulseSender();
//CONTROLLER ctr = initCONTROLLER();
PulseGen ArrPulse[] = {initPulseGen(4), initPulseGen(6)};
GUI ArrGui[] = {initGUI(0), initGUI(4)};
CONTROLLER input = initCONTROLLER();



int main(void){	
	
	
	ArrPulse[0].PS = &PS;
	ArrPulse[1].PS = &PS;
	ArrPulse[0].gui = &ArrGui[0];
	ArrPulse[1].gui = &ArrGui[1];

    input.ArrPulse[0] = &ArrPulse[0];
	input.ArrPulse[1] = &ArrPulse[1];
    input.gui[0] = &ArrGui[0];
	input.gui[1] = &ArrGui[1];
	
	INSTALL(&input, movevertical, IRQ_PCINT1);
	INSTALL(&input, movehorizontal, IRQ_PCINT0);
	
	TINYTIMBER(&input, initialize, NULL);
}

