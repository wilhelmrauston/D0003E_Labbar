#ifndef TRAFFICLIGHT_H_
#define TRAFFICLIGHT_H_

#include "TinyTimber.h"
#include <stdbool.h>
#include <stdint.h>


typedef struct TrafficLight {
  Object super;
  bool active;
 
} TrafficLight;

#define initTrafficLight(active) {initObject(), active}

void setLamp(TrafficLight *self, bool newActive);

#endif