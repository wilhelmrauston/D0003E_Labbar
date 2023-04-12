#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

extern int COM1;

extern int northQueue;
extern int southQueue;
extern int crossing;

extern bool southLight;
extern bool northLight;

extern pthread_mutex_t sl;
extern pthread_mutex_t nl;
extern pthread_mutex_t c;
extern pthread_mutex_t cm;