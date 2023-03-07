
#include <avr/io.h>
#include "Utility.h"

void initUtil (Utility *self, unsigned int ubrr){
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

    /* Set Baud Rate*/
    UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0);
	
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (0<<USBS0)|(1<<UCSZ00)|(1<<UCSZ01);
}

