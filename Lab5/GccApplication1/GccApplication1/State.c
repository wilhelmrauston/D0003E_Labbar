/*
 * GccApplication1.c
 *
 * Created: 2023-02-28 13:25:58
 * Author : Nils
 */ 

#include <avr/io.h>
#include "State.h"


void carArrived(State *self, int dir) {
    switch (dir) {
        case 1:
            self->northQueue += 1;
            if (crossing = 0) {
                if (self->currTimeout) {
                    ABORT(self->currTimeout);
                    }
                self->currTimeout = AFTER(SEC(15), self, timeout, NULL);
                ASYNC(self->northLight, setLamp, true);
            }
            break;
        case -1:
            self->southQueue += 1;
            if (crossing = 0) {
                if (self->currTimeout) {
                    ABORT(self->currTimeout);
                    }
                self->currTimeout = AFTER(SEC(15), self, timeout, NULL);
                ASYNC(self->southLight, setLamp, true);   
            }
            break;
    }
}


    //It must be safe; i.e., cars going in opposite directions must never be allowed on the bridge at the same time.
    //It may not stop making progress. This means that the situation where the bridge is empty but queued cars are not allowed to enter the bridge must never arise.
    //It may not cause starvation. That is, the controller must make sure that northbound cars are not indefinitely delayed by a steady stream of southbound cars, and vice versa.
    //If there is a queue of cars from a particular direction, better bridge utilization will be achieved by letting more than one car pass from the same direction before allowing cars from the other direction. Delay between cars from the same direction should be 1 second.
    //For our particular scenario, we will assume that a reasonable time for passing the bridge once it is entered is 5 seconds.
    //It is, however, not required to deal with cars that stop on the bridge, make u-turns, ignore green lights, ignore red lights, ignore the one-car-per-green restriction, drive at extreme speeds (high and low), etc. These are not unrealistic assumptions – few real traffic light systems are designed to detect (say) cars that stop in the middle of a crossing due to engine failure.


void timeout(State *self) {
    self->currTImeout = NULL;
    ASYNC(self->southLight, setLamp, false);  
    ASYNC(self->northLight, setLamp, false);  
}

void startCrossing(State *self, int dir) {
    AFTER(SEC(5), self, hasCrossed, dir);
}

void hasCrossed(State *self, int dir);


