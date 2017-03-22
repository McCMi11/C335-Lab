#Lab 8 
##Authors  
* Michael McCann- mimccann
* Partner: Connor Ward- conward
  
---

##Difficulties  


##What did I learn  


##Questions  
###1) In previous labs, adding a peripheral has required pin initializations. Why were able to add the nunchuk without initializing anything?

The I2C takes care of that, due to we already initialized it and that will initialize anything needed.

###2) What are the major differences between these two functions and what does that imply about communicating with the nunchuk? (Functions below)  

```c
/*  f3d_i2c.c    */
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

###3) What do all of these variables correspond to in the nunchuk?  



###4) Explain the code (below).

The code checks the nunchuck raw data it read and at the first 2 bits checks which ones are ones.  The first bit corresponds to the c button and the second bit corresponds to z button.  In binary 0 is 00, 1 is 01, 2 is 10, and 3 is 11.  However, 

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
