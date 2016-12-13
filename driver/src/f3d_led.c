//Jeremy Benedek and Brad Jones
//Driver for Final Project
//Originally from Jeremy Benedek and Shengyu Chen and Yifan Liu for Lab3

#include <stm32f30x.h>
#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>
#include <f3d_led.h>


//intializes the port and pins for the leds on the board
void f3d_led_init(void) {
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
  GPIO_Init(GPIOE, &GPIO_InitStructure);  
}
/*Turns on the appropriate led as specified by the parameter.*/
void f3d_led_on(int led) {

GPIOE->BSRR = GPIO_Pin_8 << led;
}

/*Turns off the approiate led as specified by the parameter*/ 
void f3d_led_off(int led) {
  switch(led){
    case 0:
      GPIOE->BRR = GPIO_Pin_9;//turn off 
      break;
    case 1:
      GPIOE->BRR = GPIO_Pin_10;//turn off 
      break;
    case 2:
      GPIOE->BRR = GPIO_Pin_11;//turn off 
      break;
    case 3:
      GPIOE->BRR = GPIO_Pin_12;//turn off 
      break;
    case 4:
      GPIOE->BRR = GPIO_Pin_13;//turn off 
      break;
    case 5:
      GPIOE->BRR = GPIO_Pin_14;//turn off 
      break;
    case 6:
      GPIOE->BRR = GPIO_Pin_15;//turn off 
      break;
    case 7:
      GPIOE->BRR = GPIO_Pin_8;//turn off 
      break;
  }

} 

/*Turns on all LEDs*/
void f3d_led_all_on(void) {
  int k = 0;
  for(k = 0; k<8; k++){
    f3d_led_on(k);
  }
} 

/*Turns off all LEDs*/
void f3d_led_all_off(void) {
  int k = 0;
  for(k = 0; k<8; k++){
    f3d_led_off(k);
  }
} 

/* led.c ends here */
