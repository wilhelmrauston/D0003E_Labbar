#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "Gui.h"
#include <stdint.h>

uint16_t sccMap[] = {0x1551, 0x2080, 0x1e11, 0x1b11, 0x0b50, 0x1b41, 0x1f41, 0x0111, 0x1f51, 0x1b51, 0x0000};


void initLCD(Gui *self) {
	//Part 1
	CLKPR = 0x80;
	CLKPR = 0x00;

	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
	LCDCRB = (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM0) | (1 << LCDPM1) | (1 << LCDPM2) | (1 << LCDCS);
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	LCDCRA = (1 << LCDEN) | (1 << LCDAB);

    PORTB |= (1<<PB7)|(1<<PB6)|(1<<PB4);
    PORTE |= (1<<PE2)|(1<<PE3);
	DDRB   = (1<<DDB5)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0);
	DDRE   = (1<<DDE6)|(1<<DDE4);
   
	PCMSK0 = (1<<PCINT3)|(1<<PCINT2);
	PCMSK1 = (1<<PCINT15)|(1<<PCINT14)|(1<<PCINT12);
	EIMSK = (1 << PCIE1)|(1 << PCIE0);
}

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

void printAt(Gui *self, uint8_t num) {
    int pp = self->pos;
    writeChar( (num % 100) / 10 + '0', pp);
    pp++;
    writeChar( num % 10 + '0', pp);
}

void switchActive(Gui *self) {
	if (self->pos == 0) {
		LCDDR0 ^= 0b10;
	}
	else if (self->pos == 4) {
		LCDDR1 ^= 0x1 << 6;
	}
}
