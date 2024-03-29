//Jeremy Benedek and Brad Jones
//Driver for Final Project
//Originally from Jeremy Benedek and Brad Jones for Lab10

#include <stm32f30x.h>
#include <f3d_uart.h>


//the initialization function to call
void f3d_uart_init(void) {

  GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC,&GPIO_InitStructure);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC , &GPIO_InitStructure);

  GPIO_PinAFConfig(GPIOC,4,GPIO_AF_7);
  GPIO_PinAFConfig(GPIOC,5,GPIO_AF_7);

  RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

  USART_StructInit(&USART_InitStructure);
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART1 ,&USART_InitStructure);
  USART_Cmd(USART1 , ENABLE);


  // Initialize the rx and tx queues
  init_queue(&rxbuf);
  init_queue(&txbuf);

  // Setup the NVIC priority and subpriority
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x08;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x08;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

  // Enable the RX interrupt 
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

}
//sends a character
int putchar(int c) {
  if (!queue_empty(&txbuf)) {
    flush_uart();
  }
  enqueue(&txbuf, c);
} 
//gets a character
int getchar(void) {
  int c;
  dequeue(&rxbuf, &c); 
  return c;
}
//sends a string
void putstring(char *s) {
  int c;
  while(s[c] != '\0' ){
    putchar(s[c]);
    c++;
  }
}

static int TxPrimed = 0;

void flush_uart(void) {
  USART_ITConfig(USART1,USART_IT_TXE,ENABLE); 
}

void USART1_IRQHandler(void) {
  int ch; 

  if (USART_GetFlagStatus(USART1, USART_FLAG_RXNE)) {
    ch = USART_ReceiveData(USART1);
    if (!enqueue(&rxbuf,ch)) {}    // overflow case -- 
    // throw away data and perhaps flag status
  }
  if (USART_GetFlagStatus(USART1,USART_FLAG_TXE)) {
    dequeue(&txbuf, &ch);
    if (ch) {
      USART_SendData(USART1,ch);
    }
    else {                        // Queue is empty, disable interrupt
      USART_ITConfig(USART1,USART_IT_TXE,DISABLE);
      TxPrimed = 0;               // signal putchar to reenable
    }
  }
}

/* f3d_uart.c ends here */
