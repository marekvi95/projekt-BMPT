#include "settings.h"
#include "dht.h"
#include <util/delay.h>
#include <avr/io.h>
#include <stdio.h>

uint8_t c=0 counter=0;
uint16_t timeoutcounter = 0;


void request()				/* Microcontroller send start pulse/request */
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);	/* set to low pin */
	_delay_ms(18);			/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN); /* set to high pin */

}

void response()				/* receive response from DHT11 */
{
    counter = 0;
    DDRD &= ~(1<<DHT11_PIN);
    while(PIND & (1<<DHT11_PIN))
        {
            _delay_us(1);
            counter++;
            if(counter>60)
                return;
        }
    counter = 0;
	while((PIND & (1<<DHT11_PIN))==0)
        {
            _delay_us(1);
            counter++;
            if(counter>80)
                return;
        }
    counter = 0;
	while(PIND & (1<<DHT11_PIN))
        {
            _delay_us(1);
            counter++;
            if(counter>80)
                return;
        }
}


uint8_t receive_data()			/* receive data */
{
    timeoutcounter = 0;
	for (int q=0; q<8; q++)
	{
		while(!(PIND & (1<<DHT11_PIN))) {
            timeoutcounter++;
            if(timeoutcounter > TIMEOUT) /* timeout */
                return -1;
		}  /* check received bit 0 or 1 */

		_delay_us(30);
		if(PIND & (1<<DHT11_PIN))/* if high pulse is greater than 30us */
		c = (c<<1)|(0x01);	/* then its logic HIGH */
		else			/* otherwise its logic LOW */
		c = (c<<1);

		while(PIND & (1<<DHT11_PIN)) {
            timeoutcounter++;
            if(timeoutcounter > TIMEOUT)
                return -1;
		}
	}
	return c;
}
