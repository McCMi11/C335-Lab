#Lab 3 Report
##By: Michael McCann
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

PE15- 46- R43- Uses bitshift of 3

PE11- 42-R44- Uses bitshift of 7

##What are the public attributes of the GPIO_InitTypeDef Struct?

GPIO_Pin, GPIO_Mode, GPIO_Speed, GPIO_OType, and GPIO_PuPd