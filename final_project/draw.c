/*   START draw.c   */

// local includes
#include "main.h"
#include "draw.h"

void drawRect(int x, int y, int width, int  height, uint16_t color){
  uint8_t ypos;
  uint16_t col[width];
  for (ypos = 0; ypos < width; ypos++) col[ypos] = color;
  f3d_lcd_setAddrWindow (x, y, x + width - 1, y + height - 1,MADCTLGRAPHICS);
  for (ypos=0; ypos < height; ypos++) {
    f3d_lcd_pushColor(col, width);
  }
}

// draws square of given color and at given start
// note x and y are the top left corner
void drawSquare(int x, int y, int width, uint16_t color) {
  drawRect(x, y, width, width, color);
}

// draws line from point (x0,y0) -> (x1, y1) of given color
// order doesnt matter
void drawLine(int x0, int y0, int x1, int y1, uint16_t color){
  // flip x and y if start is bigger than the end
  if(x0 > x1){
    int temp = x0;
    x0 = x1;
    x1 = temp;
  }
  if(y0 > y1){
    int temp = y0;
    y0 = y1;
    y1 = temp;
  }
  // verticle line
  if(x0 == x1){
    uint16_t col[y1-y0];
    uint8_t i;
    for(i = 0; i < y1-y0; i++) col[i] = color;
    f3d_lcd_setAddrWindow(x0,y0,x1,y1,MADCTLGRAPHICS);
    f3d_lcd_pushColor(col,y1 - y0);
    return;
  }
  // horizontal line
  if(y0 == y1){
    uint16_t col[x1-x0];
    uint8_t i;
    for(i = 0; i < x1-x0; i++) col[i] = color;
    f3d_lcd_setAddrWindow(x0,y0,x1,y1,MADCTLGRAPHICS);
    f3d_lcd_pushColor(col,x1 - x0);
    return;
  }
  // diaganol line
  int dx, dy, p, x, y;
 
  dx=x1-x0;
  dy=y1-y0;
 
  x=x0;
  y=y0;
 
  p=2*dy-dx;
 
  while(x<x1){
    if(p>=0){
      f3d_lcd_drawPixel(x,y,color);
      y=y+1;
      p=p+2*dy-2*dx;
    }else{
      f3d_lcd_drawPixel(x,y,color);
      p=p+2*dy;
    }
    x++;
  }
}




/*****************
 *   rgb24_to_rgb16
 *
 *   Input: - uint16_t R, 
 *          - uint16_t G, 
 *          - uint16_t B
 *   Assumptions of input: Order matters
 *   Guarantees about output: Outputs a single number,
 *              the rgb16, but in little endian form
 *   Description: Converts RGB24 to RGB16(little endian)
 *
 *
 */
uint16_t rgb24_to_rgb16(uint16_t R, uint16_t G, uint16_t B) {
  B = ((B & 0xFF) >> 3) << 11;
  G = ((G & 0xFF) >> 2) << 5;
  R = ((R & 0xFF) >> 3);
  return ((R | G) | B);
}

/*****************
 *   RGB565
 *
 *   Input: - char* pix
 *          - uint16_t image
 *   Assumptions of input:pix is of size 3 
 *   Guarantees about output: Outputs a single number,
 *              the rgb16, but in little endian form.
 *              Saved in image.
 *   Description: Converts RGB24 to RGB16(little endian)
 *
 */
void RGB565(char *pix, uint16_t *image){
  uint16_t color;
  color = rgb24_to_rgb16(pix[0], pix[1], pix[2]);
  *image = color;
}


/*   END draw.c   */
