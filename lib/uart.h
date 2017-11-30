/*void uart_putchar(char c, FILE *stream);
char uart_getchar(FILE *stream);*/


/* http://www.ermicro.com/blog/?p=325 */

//FILE uart_output = FDEV_SETUP_STREAM(uart_putchar, NULL, _FDEV_SETUP_WRITE);
//FILE uart_input = FDEV_SETUP_STREAM(NULL, uart_getchar, _FDEV_SETUP_READ);


void uart_init(void);
void uart_putc(unsigned char data);
void uart_puts(char str[]);
uint8_t uart_flush(void);
