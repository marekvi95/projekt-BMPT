#include "settings.h"
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "nokia5110.h"
#include "dht.h"
#include <avr/interrupt.h>


uint8_t i_RH, d_RH, i_temp, d_temp, check_sum, i_temp_f;

extern uint16_t convtof(uint16_t);
char tempset = 0;

uint16_t roundtemp(uint16_t I, uint16_t D)
{
    if (D>=5)
        return I+1;
    else
        return I;
}

int main(void)
{
    uart_init(); /* initialization of UART */
    sei(); /* enable interrupts */
    uart_puts("Press any key to change temperature units\n");

    uint16_t result;
    char data[5];

    nokia_lcd_init();
    nokia_lcd_clear();
    nokia_lcd_write_string("Engineering",1);
    nokia_lcd_set_cursor(0, 10);
    nokia_lcd_write_string("RAD&MAR", 2);
    nokia_lcd_set_cursor(0, 40);
    nokia_lcd_render();
    _delay_ms(1000);


    nokia_lcd_init();
    nokia_lcd_clear();	/* Clear LCD */
    nokia_lcd_write_string("Humidity&Temp ",1);
    nokia_lcd_set_cursor(0,10);		/* Enter column and row position */
    nokia_lcd_write_string("Initialization ",1);
    nokia_lcd_set_cursor(0,20);		/* Enter column and row position */
    nokia_lcd_write_string("Open console..",1);
    nokia_lcd_render();
    _delay_ms(1000);

    while(1)
    {
        nokia_lcd_clear();
        request();		/* send start pulse */
        response();		/* receive response */
        i_RH=receive_data();	/* store first eight bit in I_RH */
	d_RH=receive_data();	/* store next eight bit in D_RH */
	i_temp=receive_data();	/* store next eight bit in I_Temp */
	d_temp=receive_data();	/* store next eight bit in D_Temp */
	check_sum=receive_data();/* store next eight bit in CheckSum */

	if ((i_RH + d_RH + i_temp + d_temp) == check_sum){
		
		nokia_lcd_clear();
		itoa(i_RH,data,10);
		nokia_lcd_write_string("H=",2);
		nokia_lcd_write_string(data,2);
		nokia_lcd_write_string(".",2);

		itoa(i_RH,data,10);
		nokia_lcd_write_string(data,2);
		nokia_lcd_write_string("%",2);
		nokia_lcd_set_cursor(0,30);

		if(tempset) {
                    
		    i_temp = roundtemp(i_temp, d_temp);
                    result = convtof(i_temp);
                    itoa(result,data,10);
                    nokia_lcd_write_string("T=",2);
                    nokia_lcd_write_string(data,2);
                    nokia_lcd_write_string("!",1); //character for °
                    nokia_lcd_write_string("F",2);
		}
		
		else {
                
		    itoa(i_temp,data,10);
                    nokia_lcd_write_string("T=",2);
                    nokia_lcd_write_string(data,2);
                    nokia_lcd_write_string(".",2);

                    itoa(d_temp,data,10);
                    nokia_lcd_write_string(data,2);
                    nokia_lcd_write_string("!",1);
                    nokia_lcd_write_string("C",2);
		}

             nokia_lcd_render();
      }

   }
    return(0);
}


ISR(USART_RX_vect)
{
    uart_flush();
    uart_puts("Temperature units changed\n");
    tempset = !tempset;
}
