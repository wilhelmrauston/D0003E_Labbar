#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include "TinyTimber.h"
#include <stdbool.h>
#include <stdint.h>


typedef struct TrafficLight {
  Object super;
  bool act;
} TrafficLight;

#define initTrafficLight(act) {initObject(), act}

void setLamp(TrafficLight *self, bool newActive);

#endif