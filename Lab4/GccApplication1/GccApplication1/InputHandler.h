#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_


#include "TinyTimber.h"
#include "Gui.h"
#include "PulseGen.h"

typedef struct CONTROLLER {
  Object super;
  PulseGen *ArrPulse[2];
  GUI *gui[2];
  int active;
  Msg holding;
  int debounce;	
} CONTROLLER;

#define initCONTROLLER() {initObject(), NULL, NULL, 0, NULL, false, 0}

void initialize(CONTROLLER *self);

void movevertical(CONTROLLER *self);

void movehorizontal(CONTROLLER *self);

void resetDebounce(CONTROLLER *self);


#endif