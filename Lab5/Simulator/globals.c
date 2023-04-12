#include "globals.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

int northQueue = 0;
int southQueue = 0;
int crossing = 0;

bool southLight = false;
bool northLight = false;

pthread_mutex_t sl;
pthread_mutex_t nl;

pthread_mutex_t c;

pthread_mutex_t cm;
