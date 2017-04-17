/*   START draw.c   */

void line(int x0, int y0, int x1, int y1){
  int deltax = x1 - x0;
  int deltay := y1 - y0;
  float deltaerr = abs((float) deltay / (float) deltax);    // Assume deltax != 0 (line is not vertical),
  // note that this division needs to be done in a way that preserves the fractional part
  float error = deltaerr - 0.5;
  int y = y0;
  int x;
  int numPix = 0;
  for(x= x0; x <= x1; x++){
    numPix++;
    //plot(x,y);
    error = error + deltaerr;
    if(error >= 0.5){
      y = y + 1;
      error = error - 1.0;
    }
  }  
}

/*   END draw.c   */
