#Lab 8 
##Authors  
* Michael McCann- mimccann
* Partner: Connor Ward- conward
  
---

##Difficulties  

The only real difficult part we were having was the accelerometer in the nunchuk does not work that well.  We were able to combine our code somewhat quickly, due to we had almost the same setup, apart from some abstraced functions.  We chose the code that seemed to get the job done more efficiently, which was a little dificult to avoid variable names being the same.  After we combined them we only had one compiler error, first attempt, which was only a missing semicolin, which fixing that had it worked exactly as planned.

##What did I learn  

I learned it is better to abstract out more of the drawing functions to the max possible, which allows for color choice, size choice, as well as location., which I found out would be used much more than I had anticipated.  I also learned more on what the nunchuck reads and how it can determine which way the joystick is being moved, only using two variables.  

##Questions  
###1) In previous labs, adding a peripheral has required pin initializations. Why were able to add the nunchuk without initializing anything?

The I2C takes care of that, due to we already initialized it and that will initialize anything needed.  The nunchuk is an I2C.

###2) What are the major differences between these two functions and what does that imply about communicating with the nunchuk? (Functions below)  

The first TransferHandling of the nunchuk is AutoEnd_Mode instead of SoftEnd_Mode, which indicates that the nunchuk is automatically accepting the data.  The nunchuk is at reg 0x00, which is indicated by the I2C_SendData function.  This means the function can only be used for the nunchuk.  The nunchuk also clears the flags after the SendData, while th i2c1 does not.  Since the nunchuk does this it also has to wait to make sure the flags were reset.  Other than this they act the same.

```c
/*  from f3d_i2c.c    */
void f3d_i2c1_read(uint8_t device, uint8_t reg, uint8_t* buffer, uint16_t numbytes) {

  while (I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET); // Wait for I2C to become free

  I2C_TransferHandling(I2C1, device, 1, I2C_SoftEnd_Mode, I2C_Generate_Start_Write); // Send start and device address
  while (I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET); // Confirm that the transmitter empty

  if (numbytes>1) {
    reg |=0x80; // indicate that the transfer will involve multiple bytes
  }
  I2C_SendData(I2C1,reg); // Send the register address
  while (I2C_GetFlagStatus(I2C1, I2C_ISR_TC) == RESET);

  I2C_TransferHandling(I2C1, device, numbytes, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
  while (numbytes--) {
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_RXNE) == RESET);
    *buffer++ = I2C_ReceiveData(I2C1);
  }

  while (I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET); // Wait for stop flag generation

  I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
}

void f3d_i2c1_read_nunchuk (uint8_t device, uint8_t* buffer, uint16_t numbytes) {

  while (I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET);
  I2C_TransferHandling(I2C1, 0xA4, 1, I2C_AutoEnd_Mode, I2C_Generate_Start_Write);
  while (I2C_GetFlagStatus(I2C1, I2C_ISR_TXIS) == RESET);
  I2C_SendData(I2C1,0x00);
  while(I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET);
  I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
  delay(1);
  while (I2C_GetFlagStatus(I2C1, I2C_ISR_BUSY) != RESET);
  I2C_TransferHandling(I2C1, 0xA4, 6, I2C_AutoEnd_Mode, I2C_Generate_Start_Read);
  while (numbytes--) {
    while(I2C_GetFlagStatus(I2C1, I2C_ISR_RXNE) == RESET);
    *buffer++ = I2C_ReceiveData(I2C1);
  }
  while (I2C_GetFlagStatus(I2C1, I2C_ISR_STOPF) == RESET);
  I2C_ClearFlag(I2C1, I2C_ICR_STOPCF);
}
```

###3) What do all of these variables correspond to in the nunchuk? (Structure below)  

* jx: Joystick Up/Down
  - 0 = left
  - 255 = right  
* jy: Joystick Left/Right
  - 0 = down
  - 255 = up  
* ax: movement in x direction
* ay: movement in y direction
* az: movement in z direction
* c: c button
  - 0 = not pressed
  - 1 = pressed
* z: z button
  - 0 = not pressed
  - 1 = pressed  

```c
/*    from f3d_nunchuk.h: nunchuk_t    */
typedef struct nunchuk_data { 
  unsigned char jx;
  unsigned char jy;
  unsigned short ax;
  unsigned short ay;
  unsigned short az;
  unsigned char c;
  unsigned char z;
} nunchuk_t; 
```

###4) Explain the code (below).

The code checks the nunchuck raw data it read and at the first 2 bits checks which ones are ones.  The left most bit corresponds to the z button and the other bit corresponds to c button.  In binary 0 is 0b00, 1 is 0b01, 2 is 0b10, and 3 is 0b11.  However, when the two bits are the same, case 0 and 3, the result is switched.  This could be due to some carry or something.

```c
//from f3d_nunchuk_read
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
```
