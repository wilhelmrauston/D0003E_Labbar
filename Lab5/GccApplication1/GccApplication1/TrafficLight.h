#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include "TinyTimber.h"
#include <stdbool.h>
#include <stdint.h>
#include "Gui.h"


typedef struct TrafficLight {
  Object super;
  Gui *lightGui;
  int act;
} TrafficLight;

#define initTrafficLight(act) {initObject(), NULL, act}

void setLamp(TrafficLight *self, int newActive);

int getLamp(TrafficLight *self);

#endif