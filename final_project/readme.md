#Final Project
---

##Authors

1. Michael McCann: mimccann
2. Partner: Samuel Carter: sambcart

##My Tasks

###1. Code Layout

This involved setting up the code in different files to make it easier to modify and organize.  We were able to use this layout to be able to change code easier instead of using a huge main.c file.  This saved us a lot of time for searching where something may have been and what we should to to fix the issue that was happening.

###2. Set up Asteroid

This was the base of not just how the asteroids looked, but also moved and were created.  They are the main item being drawn in the game and required efficient code to draw them with as little lag as possible.  I ended up making a circle that was filled by using a circle drawing algorithm to output what the outline should be and from there made an array to fill in the circle and used push color to only push a few times instead of drawing each individual pixel, which is fast enough to draw them where they flash so fast being drawn and undrawn they look dimmer than if they were not.

###3. Set up drawing

This was actually the least important thing that I did for the project, due to most of the shapes wer not used, or were only used a couple of times, which made it have almost no effect on how the project worked.  The main one that was used was draw rect and draw line, which are basically the same thing, due to we never draw a line that isnt horrizontal or vertical, although the function supports it.  We also never use them except for drawing a couple of colors, which means they could have been used only for that and not needed the extra argument of a color.

###4. Boot/Splash setup 

This was not required, but added to the apprearance of the game, which it was also a nice challenge, due to we used 3 images on it as well as a sound, which means a lot of planning on space was required to fit all of the data in flash storage.  This was a problem, but I knew I could come up with a solution that worked and worked well.  These give the game a feature that makes it stand out from the crowd.

###5. Randomness

We use the randomness to help with placement of the asteroids, which is needed so when you click play the game is not that predictable, which with enough time you could find some kind of pattern, but that would be difficult, due to it relys on the posistion of the board as well as total time elappsed since the board got power, which changes every thousanth of a second, which is fast and most people could not calculate what the time is at.  This adds a neat aspect to the game of not knowing how the initial state will look as well as not knowing where the asteroids will spawn.

##What technical challenges did you encounter in completing your tasks?

The main one was memory in general.  We had several arrays, which one was of size 128 for the color storage to use push color fast.  There were others for the actual items in the game, which did not seem like too much space, but when it was being played it would run into some memory overflow problems and that is hard to see, due to the game would work some and fail at what seemed to be random places.  This could have been happening due to how we chose to have 3 images as well as a sound in the game, which most groups say they are lucky to get one of these in there due to the amount of space it requires to hold each item.

##What would you do differently if you could start the project over?

I would want to start earlier on the game mechanics itself instead of making it as efficient as I could for drawing.  Most of the drawing went to waste, due to it was not needed when the game was being played, but it worked well and was fast at drawing it.  The simple items we were wanting to implement seemed as if they would take little to no time and we soon found out that they were the hard parts, even though we could do each small part of the tast easily.  The combining of them was a challenge, which caused us to change how the game was played on the final day, which is a pain and hard to accomplish a working game switching how it runs with under 24 hours before it is due.
