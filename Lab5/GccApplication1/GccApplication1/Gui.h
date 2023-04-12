#ifndef GUI_H_
#define GUI_H_

#include <stdint.h>
#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"


typedef struct Gui {
  Object super;
  uint8_t pos;
} Gui;

#define initGui(pos) {initObject(), pos}

void printAt(Gui *self, uint8_t num);

void switchActive(Gui *self, uint8_t status);

#endif