/*   begin draw.h   */

/*   variables   */


/*   functions   */

void drawRect(int x, int y, int width, int  height, uint16_t color);
void drawSquare(int x, int y, int width, uint16_t color);
void drawLine(int x0, int y0, int x1, int y1, uint16_t color);
void RGB565(char *pix, uint16_t *image);
uint16_t rgb24_to_rgb16(uint16_t R, uint16_t G, uint16_t B);

/*   end draw.h   */
