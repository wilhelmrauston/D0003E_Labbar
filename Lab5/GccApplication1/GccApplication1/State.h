#ifndef STATE_H
#define STATE_H

#include "TrafficLight.h"
#include "TinyTimber.h"
#include "Gui.h"
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>

typedef struct State {
	Object super;
    int northQueue;
    int southQueue;
    TrafficLight *southLight;
    TrafficLight *northLight;
    int crossing;
    Msg currTimeout;
    Gui *gui[3];
	int initiated;
} State;

#define initState() {initObject(), 0, 0, NULL, NULL, 0, NULL, NULL, 0}


void carArrived(State *self, int dir);
void timeout(State *self);
void startCrossing(State *self, int dir);
void hasCrossed(State *self, int dir);
void initialize(State *self);


#endif