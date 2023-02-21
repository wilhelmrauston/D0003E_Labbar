/*
 * GccApplication1.c
 *
 * Created: 2023-02-14 13:11:34
 * Author : Nils
 */ 

#include <avr/io.h>
#include "Gui.h"
#include "InputHandler.h"
#include "PulseGen.h"
#include "PulseSender.h"
#include "TinyTimber.h"

//GUI gui = initGUI();
//CONTROLLER controller = initCONTROLLER();
PulseSender PS = initPulseSender();
//PulseGen ArrPulse[] = {initPulseGen(1, 4, 1), initPulseGen(0, 6, 1)};
volatile PulseGen PG1 = {initObject(), 1, 1, 1};

//ArrPulse[0]->PS = PS;
//ArrPulse[1]->PS = PS;
//PulseGen PulseGen1 = initPulseGen();


int main(void){
	PG1.PS = &PS;
    //INSTALL(&controller, movevertical, IRQ_1);
    //INSTALL(&controller, movehorizontal, IRQ_2);
    //ArrPulse[1];
    //return TINYTIMBER(&controller, meth3, val);
}

