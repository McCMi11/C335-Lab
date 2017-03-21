#Lab 8 
##Authors  
* Michael McCann- mimccann
* Partner: Connor Ward- conward
  
---

##Difficulties  


##What did I learn  


##Questions  
###1) In previous labs, adding a peripheral has required pin initializations. Why were able to add the nunchuk without initializing anything?


###2) What are the major differences between these two functions and what does that imply about communicating with the nunchuk?  


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
