#ifndef STATE_H
#define STATE_H

#include "TrafficLight.h"
#include "TinyTimber.h"
#include "Gui.h"

typedef struct State{
    int northQueue
    int southQueue
    TrafficLight southLight
    TrafficLight northLight
    int crossing
    Msg currTimeout
} State;

#define initState() {0, 0, initTrafficLight(false), initTrafficLight(false), 0, NULL}

void carArrived(State *self, int dir)
void timeout(State *self);
void startCrossing(State *self, int dir);
void hasCrossed(State *self, int dir);


#endif