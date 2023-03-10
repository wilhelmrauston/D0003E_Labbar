/*
 * GccApplication1.c
 *
 * Created: 2023-02-28 13:25:58
 * Author : Nils
 */ 

#include "State.h"


// 1 north
// -1 south


void initialize(State *self) {
	SYNC(self->gui[0], printAt, 0);
	SYNC(self->gui[1], printAt, 0);
	SYNC(self->gui[2], printAt, 0);
}

void carArrived(State *self, int dir) {
		volatile bool oppAct;
        switch (dir) {
			case 1:
				self->northQueue += 1;
				SYNC(self->gui[2], printAt, self->northQueue);
				oppAct = SYNC(self->southLight, getLamp, NULL);
				if ((self->crossing == 0) && (!oppAct)) {
					if (self->currTimeout) {
						ABORT(self->currTimeout);
						}
					self->currTimeout = AFTER(SEC(15), self, timeout, NULL);
					ASYNC(self->northLight, setLamp, true);
				}
				break;
			case -1:
				self->southQueue += 1;
				SYNC(self->gui[0], printAt, self->southQueue);
				oppAct = SYNC(self->northLight, getLamp, NULL);
				if (self->crossing == 0) {
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
    self->currTimeout = NULL;
    ASYNC(self->southLight, setLamp, false);  
    ASYNC(self->northLight, setLamp, false);
    SYNC(self->gui[0], switchActive, 0);
    SYNC(self->gui[2], switchActive, 0);  
}

void startCrossing(State *self, int dir) {
	self->crossing += dir;
	SYNC(self->gui[1], printAt, abs(self->crossing)); 
    switch (dir) {
        case 1:
            self->northQueue -= 1;
			SYNC(self->gui[2], printAt, self->northQueue);
            break;
        case -1:
            self->southQueue -= 1;
			SYNC(self->gui[0], printAt, self->southQueue);
            break;
        self->crossing += dir;
		SYNC(self->gui[1], printAt, abs(self->crossing));    
    }
    AFTER(SEC(5), self, hasCrossed, dir);
}

void hasCrossed(State *self, int dir) {

    // Once car has crossed, if its the last one on the road and other queue is waiting, switch lights
    // If no car is waiting, both lights will be red

    self->crossing -= dir;
	SYNC(self->gui[1], printAt, abs(self->crossing));   
    if (self->crossing == 0) {
        switch (dir) {
            case 1:
                ASYNC(self->northLight, setLamp, false);
                if (self->southQueue > 0) {
                    ASYNC(self->southLight, setLamp, true);
                }
                break;
            case -1:
                ASYNC(self->southLight, setLamp, false);
                if (self->northQueue > 0) {
                    ASYNC(self->northLight, setLamp, true);
                }
            if (self->currTimeout) {
                ABORT(self->currTimeout);
                self->currTimeout = NULL;
            }
        }
    }

}


