#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "globals.h"
#include "InputHandler.h"
#include "SerialPort.h"
#include "Gui.h"
#include "Simulator.h"
#include <pthread.h>


#include <stdio.h>





pthread_t input_t;
pthread_t Gui_t;
pthread_t Simulator_t; 
    

int main () {
	
	initSerialPort();

	pthread_create(&input_t, NULL, input, NULL);
	pthread_create(&Gui_t, NULL, updateGui, NULL);
	pthread_create(&Simulator_t, NULL, simulate, NULL);
	
	getLights();
}





