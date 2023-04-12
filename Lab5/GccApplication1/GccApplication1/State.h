#ifndef STATE_H
#define STATE_H

#include "TrafficLight.h"
#include "TinyTimber.h"
#include "Gui.h"
#include <stdbool.h>
#include <avr/io.h>
#include <stdlib.h>

typedef struct State {
	Object super;
    int northQueue;
    int southQueue;
    TrafficLight *southLight;
    TrafficLight *northLight;
    int crossing;
    Gui *gui[3];
	Msg currTimeout;
    Msg currNext;
} State;

#define initState() {initObject(), 0, 0, NULL, NULL, 0, NULL, NULL, NULL}


void carArrived(State *self, int dir);
void timeout(State *self, int dir);
void startCrossing(State *self, int dir);
void hasCrossed(State *self, int dir);
void initialize(State *self);
void changeLights(State *self, int newActive, int dir);
void senNext(State *self, int dir);


#endif