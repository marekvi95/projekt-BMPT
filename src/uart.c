#include <avr/io.h>
#include <avr/interrupt.h>
#include "settings.h"

/* http://www.cs.mun.ca/~rod/Winter2007/4723/notes/serial/serial.html */

void uart_init(void)
{
  unsigned int ubrr = F_CPU/16/9600-1;

  /* Set baud rate */
	UBRR0 = ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
	/* Set frame format: 8data, 1stop bit */
	UCSR0C = (3<<UCSZ00);
	UCSR0B |= 1<<RXCIE0;

}

void uart_putc(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void uart_puts(char str[])
{
  for (int i=0; str[i]; i++)
    uart_putc(str[i]);
}

uint8_t uart_flush(void)
{
    uint8_t tmp;
    tmp = UDR0;
    return tmp;
}
