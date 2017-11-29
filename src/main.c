#include "settings.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include "uart.h"
#include "nokia5110.h"
//#include "dhtxx.h"


#define DHT11_PIN 2
#define TIMEOUT 1000

uint8_t c=0,I_RH,D_RH,I_Temp,D_Temp,CheckSum;

void Request()				/* Microcontroller send start pulse/request */
{
	DDRD |= (1<<DHT11_PIN);
	PORTD &= ~(1<<DHT11_PIN);	/* set to low pin */
	_delay_ms(18);			/* wait for 20ms */
	PORTD |= (1<<DHT11_PIN); /* set to high pin */

}

void Response()				/* receive response from DHT11 */
{
    uint8_t counter = 0;
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


uint8_t Receive_data()			/* receive data */
{
    uint16_t timeoutcounter = 0;
	for (int q=0; q<8; q++)
	{
		while(!(PIND & (1<<DHT11_PIN))) {
            timeoutcounter++;
            if(timeoutcounter > TIMEOUT)
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


int main(void)
{


    nokia_lcd_init();
    nokia_lcd_clear();
    nokia_lcd_write_string("Engineering",1);
    nokia_lcd_set_cursor(0, 10);
    nokia_lcd_write_string("RAD&MAR", 2);
    nokia_lcd_set_cursor(0, 40);
    nokia_lcd_render();
    _delay_ms(1000);
    //nokia_lcd_clear();

    uart_init();
    stdout = &uart_output;
    stdin = &uart_input;

    char data[5];
    nokia_lcd_init();
	nokia_lcd_clear();			/* Clear LCD */
	nokia_lcd_write_string("Humidity&Temp ",1);
	nokia_lcd_set_cursor(0,10);		/* Enter column and row position */
	nokia_lcd_write_string("Initialization ",1);
    nokia_lcd_render();
	_delay_ms(1000);

    while(1)
	{
        //nokia_lcd_clear();
		Request();		/* send start pulse */
		Response();		/* receive response */
		I_RH=Receive_data();	/* store first eight bit in I_RH */
		D_RH=Receive_data();	/* store next eight bit in D_RH */
		I_Temp=Receive_data();	/* store next eight bit in I_Temp */
		D_Temp=Receive_data();	/* store next eight bit in D_Temp */
		CheckSum=Receive_data();/* store next eight bit in CheckSum */

        //printf("vlhkost %i\n", I_RH);
        //printf("teplota %i\n", I_Temp);
        //nokia_lcd_write_string("zkouska",1);

		if ((I_RH + D_RH + I_Temp + D_Temp) == CheckSum)

		{
			nokia_lcd_clear();
			itoa(I_RH,data,10);
			nokia_lcd_write_string("H=",2);
			nokia_lcd_write_string(data,2);
			nokia_lcd_write_string(".",2);

			itoa(D_RH,data,10);
			nokia_lcd_write_string(data,2);
			nokia_lcd_write_string("%",2);
			nokia_lcd_set_cursor(0,30);

			itoa(I_Temp,data,10);
            nokia_lcd_write_string("T=",2);
			nokia_lcd_write_string(data,2);
			nokia_lcd_write_string(".",2);

			itoa(D_Temp,data,10);
			nokia_lcd_write_string(data,2);
			nokia_lcd_write_string("C ",2);

			itoa(CheckSum,data,10);
			//nokia_lcd_write_string(data,1);
            //nokia_lcd_write_string(" ",1);
            nokia_lcd_render();
        }

	_delay_ms(10);
	}
    return(0);
}
