#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"
#include <stdbool.h>


typedef struct GUI {
  Object super;
  bool active;
} GUI;

#define initGUI() \
		{ initObject(), 0}

void InitLCD();

void printAt(GUI *self, int pos); 

void switchActive(GUI *self); 

#endif