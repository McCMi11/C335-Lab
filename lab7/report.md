#Lab 7  
##Difficulties  


##What did I learn  


##Questions  
###Q1: accelerometer/magnetometer  
####How many pins does it have?  
14 pins.
1. Vdd_IO:  Power supply for I/O pins
2. SCL: Signal interface I2C serial clock (SCL)
3. SDA: Signal interface I2C serial data (SDA) 
4. INT2: Inertial Interrupt 2
5. INT1: Inertial Interrupt 1
6. C1: Reserved capacitor connection (C1)
7. GND: 0 V supply
8. Reserved: Leave unconnected
9. DRDY: Data ready
10. Reserved: Connect to GND
11. Reserved: Connect to GND
12. SETP: S/R capacitor connection (C2)
13. SETC: S/R capacitor connection (C2)
14. Vdd: Power supply  

####How many volts (Vdd) are required to power the accelerometer/magnetometer?  
Acceleration (any axis, powered, Vdd = 2.5 V)

####Describe where it is on the board  
![Accelerometer location](https://github.iu.edu/mimccann/CS-Spring2017/blob/master/lab7/c335board.png)


---
###Q2: accelerometer/magnetometer init  
####Why do we write to the accelerometer/magnetometer before we can read from them?   

We write to the accelerometer/magnetometer first to specify what it should be able to return, how it should function, as well as power.  The accelerometer specifies power, axis, update frequency, little/big endian, sensitivity, resolution, as well as other modes.  The magnetometer specifies wether the temp sensor is used, output rate, scale, and conversion rate.

####What are the following lines of code doing?(Code Below)   

Each line of code sends a byte of data to the accelerometer/magnetometer, which is used to enable/disable features, or even specify some detail of the system.  Each byte is sent to the corresponding location in which that data is stored in the accelerometer/magnetometer.


'''
 /* f3d_accel.c*/
 value = 0x40|0x07;                 // Normal Power Mode, All Axis Enable (X,Y,Z)
 f3d_i2c1_write(0x32, 0x20, &value); // Accel (0x32), Ctrl Reg1 (0x20) 

 value = 0x08;              // Continuous Update, Little Endian, 2G Sensitivity, High Resolution Mode
 f3d_i2c1_write(0x32, 0x23, &value); // Accel (0x32, Ctrl Reg4  (0x23)

 value = 0x10 | 0x80;               // HPF Cutoff 16, High Pass Filter Normal Mode, AO1/AO1 Disable
 f3d_i2c1_write(0x32, 0x21, &value); // Accel (0x32, Ctrl Reg2  (0x21)
'''
'''
 /* f3d_mag.c */
 value = 0x14;                  //Temp sensor disable,30Hz Output Rate 
 f3d_i2c1_write(0x3C, 0x00,  &value); // Mag (0x3C), CRA (0x00) 

 value = 0xE0;                      // +/- 8.1 Gauss Full Scale
 f3d_i2c1_write(0x3C, 0x01, &value); // Mag (0x3C), CRB (0x01)

 value = 0x00;                      // Continuous Conversion
 f3d_i2c1_write(0x3C, 0x02, &value); // Mag (0x3C), MR  (0x23)
'''

---
###Q3: More f3d_accel.c Code   
####What do the following lines of code do?(Code Below)  
The code is capturing the accelerometer data.  This takes the raw data it captured and converts it to a float stored in an array, x = 0, y = 1, z = 2.  The reason it is divided by 1000 is to make the number smaller, which in return does not affect the data itself, but makes it easier to examine and work with.  The data was originally an integer, which the code above saving the raw_data uses a left shift, which it uses a left shift of 8, which translates to multiplying the original number, buffer[2*i], where i is the index of the x/y/z value, by 2 eight times, which is 256.  It then added the previous data, stored in the buffer[2*i], then finally divided that result by 16.  The answer is then stored as a signed 16 bit integer.

'''
/*f3d_accel.c*/
for (i=0; i<3; i++) {
  raw_data[i]=((int16_t)((uint16_t)buffer[2*i+1] << 8) + buffer[2*i])/(uint8_t)16;
  accel_data[i]=(float)raw_data[i]/1000.0;
}
'''

---
###Q4: Tilt
####Why might it be necessary to tilt compensate your compass computation?
It may be necessary to compensate for the tilt in the compas, due to the posistion of the board can determine if the reading is correct, for example if the board is upside down the reading can be reversed.  The other angles can do the same thing, but may not fully reverse the reading.  I believe that without compensating for the tilt the upside down reading will give an error instead of calculating any value.