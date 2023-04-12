#include "Gui.h"
#include "globals.h"

void* updateGui(void* arg) {
	
	#define CLEAR "\e[1;1H\e[2J"
	#define Green "\033[32m"
	#define Red "\033[31m"
	#define Reset "\033[0m"
	
	
	while (1) {
		pthread_mutex_lock (&nl);
		pthread_mutex_lock (&sl);
		pthread_mutex_lock (&c);
		
		
		printf(CLEAR);
		printf(
"     sQ:%d                       cQ:%d                       nQ:%d",southQueue,crossing, northQueue);
		puts(			
" 															\n"
"                     __..-:\'\':__:..:__:\'\':-..__		\n"
"                 _.-:__:.-:\'\':  :  :  :\'\':-.:__:-._ \n"
"               .\':.-:  :  :  :  :  :  :  :  :  :._:\'. \n"
"            _ :.\':  :  :  :  :  :  :  :  :  :  :  :\'.: _ \n"
"           [ ]:  :  :  :  :  :  :  :  :  :  :  :  :  :[ ] \n"
"           [ ]:  :  :  :  :  :  :  :  :  :  :  :  :  :[ ] \n"
"  :::::::::[ ]:__:__:__:__:__:__:__:__:__:__:__:__:__:[ ]::::::::::: \n"
"  !!!!!!!!![ ]!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!![ ]!!!!!!!!!!! \n"
"  ^^^^^^^^^[ ]^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^[ ]^^^^^^^^^^^ \n"
"           [ ]                                        [ ] \n"
"           [ ]                                        [ ] \n"
"           [ ]                                        [ ] \n"
"   ~~^_~^~/   \\~^-~^~ _~^-~_^~-^~_^~~-^~_~^~-~_~-^~_^/   \\~^ ~~_ ^ \n");


		printf("\n #------------| Lights |------------# \n");
		
		printf("Northbound Light: %s", (northLight)? "\033[32m ON \033[0m\n": "\033[31m OFF \033[0m\n");
		
		printf("Southbound Light: %s", (southLight)? "\033[32m ON \033[0m \n": "\033[31m OFF \033[0m \n");
		
		
		
		pthread_mutex_unlock (&nl);
		pthread_mutex_unlock (&sl);
		pthread_mutex_unlock (&c);
		
		
 
	usleep(10000);
   
	}
}