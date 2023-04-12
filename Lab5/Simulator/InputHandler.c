#include "InputHandler.h"
#include "globals.h"

void *input (void *arg) {

	fcntl(fileno(stdin), F_SETFL, O_NONBLOCK);
	#define NORTHBOUND_ARRIVE 0x1	
	#define SOUTHBOUND_ARRIVE 0x4	


	
	
	while (1) {
		fd_set rfds;					// make read set
		FD_ZERO(&rfds);					// empty set
		FD_SET(0, &rfds);				// include keyboard
		if (FD_ISSET(0, &rfds)) { // handle keypress
			char ch = getchar();
			
			switch (ch) {
				case 'n':
					pthread_mutex_lock(&nl);
					northQueue += 1;
					pthread_mutex_unlock(&nl);
					writeToAVR(0x1);
					break;
				
				case 's':
					pthread_mutex_lock(&sl);
					southQueue += 1;
					pthread_mutex_unlock(&sl);
					writeToAVR(0x4);
					break;
					
				case 'e':
					exit (0);
					break;
					
				default:
					break;
				
			}
		}
	}
}