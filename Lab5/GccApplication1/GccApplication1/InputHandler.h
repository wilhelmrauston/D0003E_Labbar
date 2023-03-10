#ifndef INPUTHANDLER_H_
#define INPUTHANDLER_H_

#include <stdbool.h>
#include <stdint.h>

#include "TinyTimber.h"
#include "State.h"
#include <avr/io.h>


typedef struct InputHandler {
  Object super;
  State *state;
} InputHandler;

#define initInputHandler() {initObject(), NULL }

void readObserver(InputHandler *self);

#endif