#include <avr/io.h>
#include <stdbool.h>
#include "TinyTimber.h"
#include "Gui.h"
#include <stdint.h>

uint16_t sccMap[] = {0x1551, 0x2080, 0x1e11, 0x1b11, 0x0b50, 0x1b41, 0x1f41, 0x0111, 0x1f51, 0x1b51, 0x0000};

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

void switchActive(Gui *self, uint8_t status) {

	// Set active signifier in gui to status

	if (self->pos == 0) {
		LCDDR0 = (LCDDR0 & ~(0x1 << 1)) | (status << 1);
	}
	else if (self->pos == 4) {
		LCDDR1 = (LCDDR1 & ~(0x1 << 6)) | (status << 6);
	}
}
