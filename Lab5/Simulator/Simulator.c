#include "Simulator.h"
#include "globals.h"


	
void* startCrossing (void* arg){

	//send signal to light
	pthread_mutex_lock (&c);
	crossing++;
	pthread_mutex_unlock (&c);
	
	usleep(5000000);
	pthread_mutex_lock (&c);
	crossing--;
	pthread_mutex_unlock (&c);
	pthread_exit(NULL);
	
	
}

void *simulate (void *arg) {
	
	
	pthread_t car_t;
	//printf("her2e");
	while(1) {
		pthread_mutex_lock(&nl);
		if (northQueue > 0 && northLight == true) {
			northQueue--;
			pthread_create(&car_t, NULL, startCrossing, NULL);
			writeToAVR(0x2);
			usleep(1000000);
		}
		pthread_mutex_unlock(&nl);
		
		pthread_mutex_lock(&sl);
		
		if (southQueue > 0 && southLight == true) {
			southQueue--;
			pthread_create(&car_t, NULL, startCrossing, NULL);
			writeToAVR(0x8);
			usleep(1000000);
		}
		pthread_mutex_unlock(&sl);
		fflush(stdin);
	}
}