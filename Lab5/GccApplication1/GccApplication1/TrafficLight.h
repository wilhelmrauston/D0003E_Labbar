#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include "TinyTimber.h"
#include <stdbool.h>
#include <stdint.h>
#include "Gui.h"
#include <avr/io.h>
#include "Writer.h"


typedef struct TrafficLight {
  Object super;
  Gui *lightGui;
  int act;
  int dir;
  Writer *wrt;
} TrafficLight;

#define initTrafficLight(act, dir) {initObject(), NULL, act, dir, NULL}

void setLamp(TrafficLight *self, int newActive);

int getLamp(TrafficLight *self);

#endif