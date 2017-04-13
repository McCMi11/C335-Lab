#Lab 1

##Author(s)
1. Michael McCann: mimccann
2. Partner: Samuel Carter: sambcart

##Difficulties

The sound was difficult to implement.  I attempted to parse through the header myself, but I could not figure out how to send the data through the audio player, which I later found was not that hard.  I also spent a while atteming to get the sound to work once I had downloaded the updated code that was supposed to work, but I was unable to do so for a while.  I later found out that it was working, but sounded awful. 

##What did you learn
I learned better on how DMA works and how to implement it.  I also learned to pay attention more to the loops and if statements.  DMA works in the background, which the same if statement would then be read over and over again, which you only want it to happen when it is true, not playing sound.

##Questions

###Question 1: What is the significance of the peripheral base address? Where does it point?

This is important so the DMA device knows where to be sending the data, or where to be taking the data from.  It also needs to be able to say which port is busy.
```c
DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&(SPIx->DR));
```

###Question 2: Why is it necessary to enable incrementing as was done in this step? What will the DMA controller do in response to this configuration.

It is important so the DMA controller can increment over the transfer buffer, which this is important if the data recieved and sent allowed is different sizes.
```c
DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)tbuf;
DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
```

###Question 3: Why is this line of the code necessary?

It allows the DMA controller to finish its transfer before some other device is allowed to access that device for data transfer, which could cause data corruption.
```c
while (DMA_GetFlagStatus(dmaflag) == RESET) { ; }
```
