//Jeremy Benedek and Brad Jones
//Driver for Final Project

#include <queue.h>
queue_t txbuf;
queue_t rxbuf;

void f3d_uart_init(void);
int putchar(int);
int getchar(void);
void putstring(char *);
void flush_uart(void);
/* f3d_uart.h ends here */
