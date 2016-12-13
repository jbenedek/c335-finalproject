//Jeremy Benedek and Brad Jones
//Driver for Final Project
//Originally from Jeremy Benedek and James Gregory for Lab8

#include <f3d_i2c.h>
#include <f3d_nunchuk.h>
#include <stdio.h>

#define NUNCHUK_ADDRESS 0xA4

void f3d_nunchuk_init(int x) {
  uint8_t realb = 0x00;
  uint8_t buf = 0x55;
  uint8_t buf2 = 0x00;
  if(x==1){  

  // Use for factory Wii Nunchuk controllers
  // f3d_i2c1_write(NUNCHUK_ADDRESS,0x40,&realb);
  // Use for 3 party nunchuks like we have in the lab
   f3d_i2c1_write(NUNCHUK_ADDRESS,0xf0,&buf,I2C1); 
   f3d_i2c1_write(NUNCHUK_ADDRESS,0xfb,&buf2,I2C1);
   }
else{
  f3d_i2c1_write(NUNCHUK_ADDRESS,0xf0,&buf,I2C2);
   f3d_i2c1_write(NUNCHUK_ADDRESS,0xfb,&buf2,I2C2);

}

}

void f3d_nunchuk_read(nunchuk_t *n,int x) {
 
  uint8_t data[6] = {0,0,0,0,0,0};
  int i;
  unsigned short tmp;
  
  if(x==1){
  f3d_i2c1_read_nunchuk(0xA5, data, 6,I2C1);
  }
  else{
  f3d_i2c1_read_nunchuk(0xA5,data,6,I2C2);
  }
  n->jx = data[0];
  n->jy = data[1];

  tmp = data[2];
  tmp = tmp << 2;
  n->ax = tmp | ((data[5] & 0x0C) >> 2);

  tmp = data[3];
  tmp = tmp << 2;
  n->ay = tmp | ((data[5] & 0x30) >> 4);

  tmp = data[4];
  tmp = tmp << 2;
  n->az = tmp | ((data[5] & 0xC0) >> 6);

  switch (data[5] & 0x03) {
  case 2:
    n->z = 1;
    n->c = 0;
    break;
  case 1:
    n->z = 0;
    n->c = 1;
    break;
  case 0:
    n->z = 1;
    n->c = 1;
    break;
  case 3:
    n->z = 0;
    n->c = 0;
    break;
  }
}

/* f3d_nunchuk.c ends here */
