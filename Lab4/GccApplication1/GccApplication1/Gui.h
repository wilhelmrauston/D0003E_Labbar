#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"
#include <stdbool.h>
#include <stdint.h>


typedef struct GUI {
  Object super;
  uint8_t pos;
} GUI;

#define initGUI(pos) {initObject(), pos}

void initLCD(GUI *self);

void printAt(GUI *self, uint8_t num);

void switchActive(GUI *self);

#endif