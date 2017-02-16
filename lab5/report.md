#Lab 5
##Authors
* Michael McCann- mimccann  
* Ross Simpson - rosssimp ... I think  

##Questions
###What does the CS pin do (the CS pin is called SS in the lab manual)?  
It allows for the selection of a chip, when multiple are connected.  From there the desired communication of bits can be done, send or recieve.

###Why do you set the CS high at the end of the pin initializations? What other functions in f3d_gyro.c change CS from low to high or high to low?  
####Description  
The TX expects to start with a CS low at the beginning followed by 8 bits and then the CS high, meaning that the data was sent.  This is to allow for a continuous stream of data to be sent and the device to know where the data starts and stops.  Setting this in the initializations allow for the device to know that it is not being used yet, but is ready to be used.  Only one SS should be set to low at a time, otherwise there could be some data being messed up, due to more than one may be attempting to send or recieve data.

####Found in:  
*f3d_gyro_interface_init  
*f3d_gyro_read  
*f3d_gyro_write  

###How do you hook up multiple peripherals on one SPI bus?  
Each slave will need its own separate SS line.  Each one should be kept at high and only turned to low when it is being used.  The SS line will be a bit, which determines high or low, low being ready to send/recieve and high being not ready.  The one that is set to low is the only one that can communicate.

###The STM has an Operating Frequency of 72 MHz. When initializing SPI1, what do you set the baud rate prescaler to? What is the resulting SPI clock frequency?  


###Does a peripheral (slave) need to be configured with the transmission speed before it can communicate with the microcontroler (master)? Why would you want to be able to do on-the-fly changes in transmission speed?  
Yes, this is due to if it is too fast or slow it may not send the data properly.  This can reslut in data loss.  We would want to be able to change the transmission speed on-the-fly due to different pieces of the microcontroller may want data to be sent or transmitted at different speeds and both need to be operating at the same speed to avoid data loss.  This allows for the data to be sent safely.  If there was not an option to change it on-the-fly it would need to be set low where each piece that needs to use it can operate at that speed, which may slow the system down.

##Difficulties  
One major difficulty I had was my partner, I got volunteered to be with someone that did not do any of the previous labs and in order for us to go at all we had to backup and do the bare minimum of the previous labs to allow this lab to be done at all.  I also had to basically train him on github and simple linux commands that he should have already known.  This was a big setback where we did not even get to the main part of the lab and I was forced to work by myself.  This meant that I had to go to the lab throughout the week to get done at all.

The second diffuclty I had was with the debugging part, I could not figure out what was wrong, other than on the char it needed to save one more bit, due to the char is one byte and was only saving 7 bits, which caused the answer to be wrong.  


##Screenshot

![Screenshot of logic analyzer](https://github.iu.edu/mimccann/CS-Spring2017/blob/master/lab5/Screenshot.png?raw=true)