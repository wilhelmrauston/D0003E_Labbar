#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include "TinyTimber.h"
#include "Gui.h"
#include "PulseGen.h"

typedef struct CONTROLLER {
  Object super;
  GUI gui;
  int frequency;

} CONTROLLER;

#define initCONTROLLER(gui) \
		{ initObject(), gui, 0}



#endif