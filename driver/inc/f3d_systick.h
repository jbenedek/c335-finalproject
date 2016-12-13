//Jeremy Benedek and Brad Jones
//Driver for Final Project

#include <stm32f30x.h>

#define SYSTICK_INT_SEC 100

void f3d_systick_init(void);
void setDen(int a);
void SysTick_Handler(void);
void f3d_systick_disinit(void);

/* f3d_systick.h ends here */
