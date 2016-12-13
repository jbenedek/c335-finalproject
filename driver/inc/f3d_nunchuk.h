//Jeremy Benedek and Brad Jones
//Driver for Final Project

#include <stm32f30x.h>

typedef struct nunchuk_data { 
  unsigned char jx;
  unsigned char jy;
  unsigned short ax;
  unsigned short ay;
  unsigned short az;
  unsigned char c;
  unsigned char z;
} nunchuk_t; 

void f3d_nunchuk_init(int x);
void f3d_nunchuk_read(nunchuk_t *,int x);

/* f3d_nunchuk.h ends here */
