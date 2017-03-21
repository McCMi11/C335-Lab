#Lab 8 
##Authors  
* Michael McCann- mimccann
* Partner: Connor Ward- conward
  
---

##Difficulties  


##What did I learn  


##Questions  
###In previous labs, adding a peripheral has required pin initializations. Why were able to add the nunchuk without initializing anything?  


###What are the major differences between these two functions and what does that imply about communicating with the nunchuk?  


###What do all of these variables correspond to in the nunchuk?  


###Explain the code (below).

'''c
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
'''
