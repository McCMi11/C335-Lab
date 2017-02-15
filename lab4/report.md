# Lab Report 4
## Authors  
* Michael McCann: mimccann
* Partner: Samuel Carter: sambcart  
---

## Questions
### How many connections are required to communicate over UART?  

Communication over the UART only requires one additional USB cable, but within the board itself it requires two wires to make the connection from the board to the UART, the transmit and recieve.  The ground wire can be needed as well, if it is not already grounded.

### What is the purpose of "alternate functions" for GPIO pins?  

You can select the purpose on an as needed basis, for example if you need to transmit data with the pin you can and then you can switch it to recieve if needed directly after.  

### Define "baud rate" in your own words.  

Speed in which the data can be transmitted and/or recieved from point A to point B.  This will vary from system to system, as well as each different piece of the system.

### Why do we need newlib_stubs? Specifically, is there a reason that printf won't work on the board without it?  

The newlib_ stubs is needed so printf will work due to it is setting the standard in, standard out, and standard error to be the computer it is connected to instead of the default, which is the board itself.  The prinf function by default will print to stdin (standard in) and that by default is the board itself, thus making printf useless without using the newlib_ stubs  

### Give an example of a situation in which the Salae Logic Analyzer is the best debugging method and include a screen shot of the Logic application.  

Th Salae Logic Analyzer is the best debugging method to be checking which inputs and outputs the board is getting.

![Screenshot of Salae Logic Analyzer program](https://github.iu.edu/mimccann/CS-Spring2017/blob/master/lab4/saleae-logic-analyzer.png?raw=true)

---
## What did you learn, any difficulties you had.  

I learned a method to debug the board itself, using the UART and the Logic Analyzer.  This was helpful to learn becuse gdb is a great tool, but can not analyze the board as it is running and test different inputs as easily.  One major diffuculty I had is that my account, not the board or computer, will not work with the make download.  My code will compile fine, but I constantly get error 255, which i was told was hardware.  I had my code checked on one of the AI's computer and it worked, but when I tried it with the same computer and board they used I would get the same error.  We checked the bashrc file to see if the path was not set, but it appears to be correct and the computer was recongizing the device under /dev/ttyUSB0.  

