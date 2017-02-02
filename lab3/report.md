#Lab 3 Report
##Created by
- Michael McCann - mimccann
- Partner: Bridges, Dyson - drbridge  

---
##What are specs of the board you are using (ex. Speed, RAM, Flash)?
1. 72 MHz Clock
2. 128K Flash
3. 32bit proccessor
4. 8K SRAM

##What does GPIO stand for?

General-purpose input/output.  This is used only when defined and are default unused.  The use is specified at run time by the user.  They do not have a specific purpose until defined.  

##Is the provided delay function accurate? Why or why not?

QUESTION IS DISREGARDED.

##What are the Port and Pin Numbers of the two Green LEDs?

Pin 11 of GPIOE, port E. A bitshift of 3 from GPIOE pin 8.

Pin 15 of GPIOE, port E. A bitshift of 7 from GPIOE pin 8.

##What are the public attributes of the GPIO_InitTypeDef Struct?

GPIO_Pin, GPIO_Mode, GPIO_Speed, GPIO_OType, and GPIO_PuPd

##Difficulties

The main thing that I found difficult was the instructions.  They were worded in a way as if I had read the entire lab already and knew to go to near the bottom for help with one thing.  One place in the lab it told us to try and compile some code it gave us, but we had to find help further down.  I was able to find it in the documentation based on the result we were getting, but it did not help that much, since it wanted us to do the following: 

>\#include "f3d_led.h"

This suggests that we have f3d_led.h in our current working directory, but we did not, which made the documentation not much help, other than pointing out an error.  However further down the lab page it says to do that, but act as if it were in the default directory, using <>.  This was not clear that we needed it or how to use it once we found the problem, which made the lab more difficult than it should be.

One other thing that I saw being a problem is how things were worded as well.

> The sequence should start with all leds off and and then end with all leds on. With exception of the all leds on state, only one led should be on at a time.

To me this sounds like it should turn an led on then back off only allowing one to be on at a time, but in lab I was told to turn them on in a circular motion, then turn them off in the circular motion.  This is one of a few cases this happend where the instructions were worded where I did not know what I should do.  This ties into me not knowing what I needed to do in the drivers, which the lab manual helped explain and clarify, but the lab itself confused me.  This was in the init part of the driver.