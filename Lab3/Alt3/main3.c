#include "tinythreads.h"
#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>
#include <avr/interrupt.h>


uint16_t sccMap[] = {0x1551, 0x2080, 0x1e11, 0x1b11, 0x0b50, 0x1b41, 0x1f41, 0x0111, 0x1f51, 0x1b51, 0x0000};

mutex MTX_BTN = MUTEX_INIT;
mutex MTX_BLK = MUTEX_INIT;
long numPressed = 0;
bool prev = false;

void LCD_Init(void) {
	//Part 1
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
	LCDCRB = (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM0) | (1 << LCDPM1) | (1 << LCDPM2) | (1 << LCDCS);
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
	
	return;
}


typedef struct blinkData {
	uint16_t nextVal;
	uint16_t oldVal;
	bool needsWrapped;
	bool wrapped;
}blinkData; 



void writeChar(char ch, int pos) {
	
	
	// Chars 0-9 + a blank
	
	//uint16_t sccMap[] =
	
	uint8_t mask;
	
	uint8_t *writePos = &LCDDR0;
	
	
	if (pos > 5 || pos < 0) {
		return;
	}
	
	
	// Convert from char representation to integer
	uint8_t intCh = ch - '0';
	
	if (intCh > 9 || intCh < 0) {
		intCh = 10;
	};
	
	// Decide which reg
	writePos += pos >> 1;
	
	// Decide of upper or lower nibble of reg
	if (pos % 2 == 0) {
		mask = 0x0f;
	}
	else {
		mask = 0xf0;
	}
	
	uint16_t sccChar = sccMap[intCh];
	
	// Repeat for all four nibbles
	for (int i = 0; i < 4; i++) {
		// Get relevant nibble
		uint8_t writeCh = (sccChar >> i*4) & 0xf;
		
		// Reset nibble to write, if i = 0 we do not want to overwrite the middle bits
		if (i == 0) {
			*writePos = (*writePos & ~mask) | (*writePos & 0x66);
			} else {
			*writePos = *writePos & ~mask;
		}
		
		
		// Duplicate nibble to upper and mask to write to upper or lower nibble of reg
		*writePos = ((writeCh | (writeCh << 4)) & mask) | *writePos;
		
		// Next nibble
		writePos += 5;

	}
	return;
	
	
}

bool is_prime(long i) {
	
	// Check for division with every number
	for(long j = 2; j < i; j++) {
		if (i % j == 0) {
			return false;
		}
	}
	return true;
}

void printAt(long num, int pos) {
    int pp = pos;
    writeChar( (num % 100) / 10 + '0', pp);
	for(volatile int i = 0; i < 1000; i++);
    pp++;
    writeChar( num % 10 + '0', pp);

}

void primes() {
    long i = 0;
	while(1) {
		if (is_prime(i)) {
			printAt(i, 0);
		}
		i += 1;
	}
}

void blink() {
	LCDDR0 = (LCDDR0 & 0xfd) | ((~LCDDR0) & 0x2);
	//LCDDR0 = !LCDDR0;
}


void button() {
	LCDDR0 =  (LCDDR0 & 0xbb) | ((~LCDDR0) & 0x44);
	numPressed += 1;
	printAt(numPressed, 4);
}

ISR(TIMER1_COMPA_vect) { //Blink
	spawn(blink, 0);
}

ISR(PCINT1_vect) { //Button
	if(!(PINB & (1<<PINB7))) {
		spawn(button, 0);
	}
}

	


int main(void)
{
    CLKPR = 0x80;
	CLKPR = 0x00;
    LCD_Init();
	LCDDR0 = LCDDR0 | (1 << 2);
    spawn(blink, 0);
	primes();
	//Create while loop to make sure it doesnt exit main() (question)
}

