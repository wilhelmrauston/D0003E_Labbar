#include "SerialPort.h"
#include "globals.h"		
int COM1;


void initSerialPort (void) {

	COM1 = open("/dev/ttyS4", O_RDWR);
	
	if (COM1 < 0) {
		printf("cant open file");
		exit(-1);
	}
	struct termios termios_p;
	if (tcgetattr(COM1, &termios_p) < 0){
		printf("couldnt get termios attributes! \n");
		exit(-1);
	}
	tcflush(COM1, TCIFLUSH); 
	
	termios_p.c_cflag = B9600 | CS8 | CREAD | CLOCAL;

	termios_p.c_cc[VTIME] = 10;
	termios_p.c_cc[VMIN] = 1;
	
	cfsetispeed(&termios_p, B9600);
	cfsetospeed(&termios_p, B9600);	
	
	if (tcsetattr(COM1, TCSANOW, &termios_p)) {
		printf("couldnt get termios attributes! nr2 \n");
		exit(-1);
	}
}

void writeToAVR(uint8_t instruction) {

	pthread_mutex_lock(&cm);
	if (write(COM1, &instruction, sizeof(instruction)) < 0) {
		printf("Couldn't write instruction to avr! \n");
	}
	pthread_mutex_unlock(&cm);
}

void getLights() {

	char recieved;
	

	while (1) {
	
		pthread_mutex_lock(&cm);
		int text = read(COM1, &recieved, sizeof(recieved));
		pthread_mutex_unlock(&cm);

		if (text > 0) {
					//printf("%d \n",recieved);
			pthread_mutex_lock(&nl);
			
			if (recieved & (1 << 0)){
				northLight = true;
				//printf("NLTRUE /n");
			}
			else if (recieved & (1 << 1)) {
				northLight = false;
				//printf("NLFALSE /n");
			}
			
			pthread_mutex_unlock(&nl);
			pthread_mutex_lock(&sl);
			
			if (recieved & (1 << 2)) {
				southLight = true;
				//printf("SLTRUE/n");
			}
			else if (recieved & (1 << 3)) {
				southLight = false;
				//printf("SLFALSE/n");
			}
			pthread_mutex_unlock(&sl);
		}
		
	}
}



