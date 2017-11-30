#include "settings.h"
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdlib.h>
#include "uart.h"
#include "nokia5110.h"
#include "dht.h"


uint8_t I_RH,D_RH,I_Temp,D_Temp,CheckSum, I_Temp_F;

extern uint16_t convtof(uint16_t);

uint16_t roundtemp(uint16_t I, uint16_t D)
{
    if (D>=5)
        return I+1;
    else
        return I;
}

int main(void)
{

    uint16_t result;
    char data[5],tempset;

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
    printf("Press f to show temeperautre in F, press any key to show temperature in C\n");


    nokia_lcd_init();
	nokia_lcd_clear();			/* Clear LCD */
	nokia_lcd_write_string("Humidity&Temp ",1);
	nokia_lcd_set_cursor(0,10);		/* Enter column and row position */
	nokia_lcd_write_string("Initialization ",1);
	nokia_lcd_set_cursor(0,20);		/* Enter column and row position */
	nokia_lcd_write_string("Open console",1);
    nokia_lcd_render();
	_delay_ms(1000);
	tempset = getc(stdin);
	printf("Initialization of the sensor\n");

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

			if(tempset == 'f') {
                I_Temp = roundtemp(I_Temp, D_Temp);
                result = convtof(I_Temp);
                itoa(result,data,10);
                nokia_lcd_write_string("T=",2);
                nokia_lcd_write_string(data,2);
                nokia_lcd_write_string("!",1); //character for °
                nokia_lcd_write_string("F",2);
			}
			else {
                itoa(I_Temp,data,10);
                nokia_lcd_write_string("T=",2);
                nokia_lcd_write_string(data,2);
                nokia_lcd_write_string(".",2);

                itoa(D_Temp,data,10);
                nokia_lcd_write_string(data,2);
                nokia_lcd_write_string("!",1);
                nokia_lcd_write_string("C",2);
			}

			//itoa(CheckSum,data,10);
			//nokia_lcd_write_string(data,1);
            //nokia_lcd_write_string(" ",1);
            nokia_lcd_render();
        }

	_delay_ms(10);
	}
    return(0);
}
