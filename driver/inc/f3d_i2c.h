//Jeremy Benedek and Brad Jones
//Driver for Final Project

#include <stm32f30x.h>

void f3d_i2c1_init();
void f3d_i2c1_read(uint8_t device, uint8_t reg, uint8_t* buffer, uint16_t numbytes);
void f3d_i2c1_read_nunchuck (uint8_t device, uint8_t* buffer, uint16_t numbytes,I2C_TypeDef* I2Cx);
void f3d_i2c1_write(uint8_t device, uint8_t reg, uint8_t* value,I2C_TypeDef* I2Cx);


/* f3d_i2c.h ends here */
