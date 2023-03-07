#ifndef GUI_H_
#define GUI_H_

#include "TinyTimber.h"
#include <stdbool.h>
#include <stdint.h>


typedef struct Gui {
  Object super;
  uint8_t pos;
} Gui;

#define initGui(pos) {initObject(), pos}

void initLCD(Gui *self);

void printAt(Gui *self, uint8_t num);

void switchActive(Gui *self, uint8_t status);

#endif