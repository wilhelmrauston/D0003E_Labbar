/*
 * GccApplication1.c
 *
 * Created: 2023-01-20 13:12:04
 * Author : Nils
 */ 

#include <avr/io.h>
#include <stdbool.h>
#include <stdint.h>


uint16_t sccMap[] = {0x1551, 0x2080, 0x1e11, 0x1b11, 0x0b50, 0x1b41, 0x1f41, 0x0111, 0x1f51, 0x1b51, 0x0000};


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

void writeLong(long i) {
	uint8_t lsd;
	
	for (int j = 0; j < 6; j++) {
		// Get lowest digit
		
		lsd = i % 10;
		
		if (i > 0) {
			writeChar((char)(lsd + '0'), 5-j);
		}	
		
		// Remove lowest digit
		i = (i - lsd) / 10;
				

	}
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

void primes() {
	for (long i = 2; i < 1000000; i++) {
		if (is_prime(i)) {
			writeLong(i);
		}
	}
	return;
}

void blink() {
	uint16_t nextVal = 31250/2;
	while(1) {
		if ((uint16_t)TCNT1 == nextVal) {
			nextVal = nextVal + 31250/2;
			if (nextVal > (2^16)) {
				
				// If wrap will occur
				nextVal = nextVal - (2^16);
			}
			
			// Negate bit 1
			LCDDR0 = (LCDDR0 & 0xfd) | ((~LCDDR0) & 0x2);
		}
	}
	return;
}

void button() {
	LCDDR0 = LCDDR0 | (1 << 2);
	bool prev = false;
	while(1) {
		if (((PINB >> 7) & 0x1) == 0) {
			if (!prev) {
				// Shift the displays
				LCDDR0 =  (LCDDR0 & 0xbb) | ((~LCDDR0) & 0x44);
			}
			prev = true;
		} else {
			prev = false;
		}
	}
}

	
void primes2(long i) {
	if (is_prime(i)) {
		writeLong(i);
	}
	return;
}

blinkData blink2(blinkData bd) {

	uint16_t currVal = (uint16_t)TCNT1;
	
	// Covers cases where counter has wrapped around and the wrap was expected
	// as well as a case where the counter was close to wrapping yet did not have
	// time to expect the next value to wrap.

	if (((currVal >= bd.nextVal) && (~bd.needsWrapped || bd.wrapped)) || (bd.wrapped && ~bd.needsWrapped)) {
		bd.nextVal = currVal + 31250/2;
		if (bd.nextVal > (2^16)) {
				
			// If wrap will occur
			bd.nextVal = bd.nextVal - (2^16);
			bd.needsWrapped = true;
			bd.wrapped = false;

		} else {
			bd.needsWrapped = false;
		}
		 
			
		// Negate bit 1
		LCDDR0 = (LCDDR0 & 0xfd) | ((~LCDDR0) & 0x2);
	}
	if (currVal < bd.oldVal) {
		bd.wrapped = true;
	}

	bd.oldVal = currVal;
	return bd;
}


bool button2(bool prev) {
	if (((PINB >> 7) & 0x1) == 0) {
		if (!prev) {
			// Shift the displays
			LCDDR0 =  (LCDDR0 & 0xbb) | ((~LCDDR0) & 0x44);
		}
		prev = true;
		} else {
		prev = false;
	}
	return prev;
	
}
	

void LCD_Init(void) {
	//Part 1
	LCDCCR = (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1) | (1 << LCDCC0);
	LCDCRB = (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM0) | (1 << LCDPM1) | (1 << LCDPM2) | (1 << LCDCS);
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
	
	//Part 2
	TCCR1B = (1 << CS12);
	return;
}


int main(void)
{
	CLKPR = 0x80;
	CLKPR = 0x00;
	PORTB = PORTB | (1 << PB7);
    LCD_Init();
	//writeChar('0', 0);
	//writeLong(123456789);
	//primes();
	//blink();
	//button();
	LCDDR0 = LCDDR0 | (1 << 2);
    long i = 25000;
	bool prev = false;
	blinkData bd;
	bd.needsWrapped = false;
	bd.wrapped = false;
	bd.nextVal = 32150/2;
	bd.oldVal = 0;
    while (1) 
    {
		primes2(i);
		i += 1;
		bd = blink2(bd);
		prev = button2(prev);
		

    }
}

