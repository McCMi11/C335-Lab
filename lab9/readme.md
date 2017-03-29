#Lab 9
##Author
* Michael McCann: mimccann
* Partner Samuel Carter: sambcart  

##Difficulties 

The hardest part was figuring out how to use the GIMP generated macro.  I was able to figure out how to draw an 8 bit image without the macro, but still needed to know how to use the macro, due to the other image we had was 24 bit.  The next difficulty I had was attempting to understand how the rotation worked, I knew there was some macro or variable that determined the location, but did not know how to use it or where it was located.  I attempted using cat and grep looking for some sort of orrientation and had no luck.  I did not know where to look in the lab manual so that was also difficult.

##What did I learn

Through mostly trial and error I was able to find out how the screen orrientation works, it was an 8 bit number, but only cared about the 3 least significant.  The first bit of those 3 relates to top and bottom, the next is left and right, and the last is portrait and landscape.  When I found out that it allowed me to notice I could make a new drawPixel function that takes that as a direction.  I also learned how to use the macros without having some kind of memory issue and correctly extract the colors.

##Questions
###What are we doing here and how does it relate to what we know about SPI?

If we used the flash memory, a SD card, we would be using another slave select (SS) line to use the SD card.  The LCD also has its own SS, which we use to write data to the LCD, typically colors, but could be any data, but the LCD will handle the data as if it were colors.

###Read chapter 12 in the lab manual which covers DMA (direct memory access). Why might DMA be important in improving the performance of your image display application?

I would be able to draw 735,000 pixels/second, which most likely would be lower.  The total number of pixels on the screen is 20,480, which means it would take 20,480/(735,000 pixels/second), or roughly 28 milliseconds, which would appear near instant, due to this is slightly over 35 fps, which is what most videos are played back in.  There would be a slow down, due to other code that needed to be calculated, but it still should be able to appear almost instant, which means redrawing would not be as time intensive as it is now.