//Jeremy Benedek and Brad Jones
//Driver for Final Project
//Originally from Jeremy Benedek and Brad Jones for Lab10

#include <f3d_systick.h>
#include <f3d_led.h> 
#include <f3d_user_btn.h>
#include <f3d_uart.h>


volatile int systick_flag = 0;

void f3d_systick_init(void) {
  SysTick_Config(SystemCoreClock/100);
}

int k = 2;
int den =25;

void setDen(int a){
	den=a;
}

void f3d_systick_disinit(void){
  SysTick_Config(0);
}

//Recommend Den values: 25 30 35 40 45
void SysTick_Handler(void) {
    f3d_led_all_off();
    f3d_led_on(k % 8);
  //  printf("%d", k);
    k++;
  
    if(user_btn_read() == 1){
      SysTick_Config(1);
    }
    else { SysTick_Config(SystemCoreClock/den);
    }
}

/* f3d_systick.c ends here */
