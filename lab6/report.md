#Lab 6  
##Authors  
* Michael McCann - mimccann  
* Taylor Smith   - tayjsmit  

---  
##Questions  
###Discuss the advantages and disadvantages of printf debugging?  
####Advantages   
Some advantages of using printf is that you can write custom messages at key points that you are looking at.  This also allows you to examine what the data looks like at each point, assuming you have printf everywhere.

####Disadvantages   
One major disadvantage is that you can possibly have data coming at the terminal extremely fast, which can lead to it being a pain debugging.  You can also have an error in a part of the code, which you did not plan for, which would not appear at all then.  Sometimes you may have the data right, which has a bad pointer or something which would make this not work.  You also could not make it to stop at a given point.

###Explain why the spiReadWrite function is called inside a higher level peripheral function (the lcdWrite function).   
It is used to set up the communication with the LCD.  If this were called in another place it could lead to problems setting up the LCD multiple times, or in different ways.

###Why does LCD_CS_DEASSERT() do? Why is it important?   
It is used to signal that we are done communicating with the LCD.  The signal is sent to the SPI master.

###Explain how the character data from the ASCII array in glcdfont.c gets converted to pixels.   
It has each character stored 5 bytes, which each byte represent a collumn in an pixel array.  Since the byte is made up of 8 bits each bit is a single pixel.  When the bit is 1 it says to turn on that pixel, which in return draws that character.

###Give the exact timing difference between the two versions of f3d_lcd_fillScreen, from the Salae analyzer, and explain why the new function is faster.   


##Screenshot

![Screenshot of logic analyzer](https://github.iu.edu/mimccann/CS-Spring2017/blob/master/lab6/screenshot.png?raw=true)

##Difficulties  
The main difficulty I had was with the LCD screen.  We were attempting to use the lcd_backlight_on(), but it kept turning off instead of staying on.  Throgh trial and error we found that without using that function it would actually turn on and stay on.  The other trouble I had was figuring out how big the screen was and which direction would start at point (0,0) and such to draw where I waned to.
