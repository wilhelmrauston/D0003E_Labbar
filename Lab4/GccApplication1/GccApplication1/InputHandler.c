#include <avr/io.h>
#include <stdbool.h>

#include "TinyTimber.h"
#include "Gui.h"
#include "PulseGen.h"

typedef struct CONTROLLER{
    Object super;
    GUI gui;
    int frequency;
} CONTROLLER;

void initialize (CONTROLLER *self) {
    SYNC(self->gui, initLCD, NULL);
    //ASYNC PG 1 & 2 , NULL ?



}

void movehorizontal () {

}

void movevertical () {

}