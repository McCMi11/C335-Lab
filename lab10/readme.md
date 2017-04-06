#Lab 10

##Author(s)
1. Michael McCann: mimccann
2. Partner: Samuel Carter: sambcart
3. Ryan also helped some.

##Difficulties

One difficulty I had was on using the queue.  I did not know that I had to include the queue.h in places of which did not appear to use the queue, but called a function that did.  Another thing that we had trouble with was figuring out where to place the LED code.  Our first thought was to place it in a while(1) loop and use Delay(int n), a function in which we defined in the systic driver file, which used the timer to wait for the number of ticks before continuing.  However this was not the correct way to do this, which we found out later.  Ryan guided me in the correct direction.

##What did you learn
One thing we learned is how usefull the lab manual can be, it nearly had the complete lab done inside of it if you actually read it, which we did and that helped.  I also learned that the lab manual has extra information in it, which can be helpful for other labs or for the final project.  One last thing I learned is that I do not need a while(1) loop to allow my program to continue running, which was due to systic.