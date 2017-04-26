/*  begin main.c   */

// local includes
#include "game.h"
#include "main.h"
#include "draw.h"

// images
#include "kickAsteroid.h" // title screen
#include "samFinger.h" // finger for pointing
#include "STMLogo.h"  // STMLogo for boot

// sounds
#include "Scream.h"

#define TIMER 20000
#define AUDIOBUFSIZE 128
int play();
extern uint8_t Audiobuf[AUDIOBUFSIZE];
extern int audioplayerHalf;
extern int audioplayerWhole;

struct ckhd {
  uint32_t ckID;
  uint32_t cksize;
};

struct fmtck {
  uint16_t wFormatTag;
  uint16_t nChannels;
  uint32_t nSamplesPerSec;
  uint32_t nAvgBytesPerSec;
  uint16_t nBlockAlign;
  uint16_t wBitsPerSample;
};

struct ckhd readckhd2(unsigned char * data, struct ckhd * hd, uint32_t ckID);

void boot(){
  char *data = STMLogo_data;
  int i, k;
  uint16_t hexColor;
  uint16_t BG;
  uint8_t offset = (128 - STMLogo_width)/2;
  uint8_t offsety = (160 - STMLogo_height)/2;
  // setting background color
  STM_LOGO(data, pixel);
  RGB565(pixel, &BG);
  f3d_lcd_fillScreen(BG);
  data = STMLogo_data;
 
  for(k = 0; k < STMLogo_height; k++){
    for(i = 0; i < STMLogo_width; i++){
      STM_LOGO(data, pixel);
      RGB565(pixel, &hexColor);
      title[i] = hexColor;
    }
    f3d_lcd_setAddrWindow (offset,k+offsety,STMLogo_width-1 + offset,k+offsety,MADCTLGRAPHICS);
    f3d_lcd_pushColor(title,STMLogo_width);
  }
  i = 500;
  k = 0;
  while(i--){
    drawSquare(k, offsety+STMLogo_height+5, 4, BLACK);
    delay(10);
    drawSquare(k, offsety+STMLogo_height+5, 4, BG);
    k = (k + 4) % 128; 
  }
  play();
  delay(500);
  splash();
}

void splash(){
  struct nunchuk_data nunck;

  //f3d_lcd_fillScreen(WHITE); // remove at end
  int i, k;
  uint16_t hexColor;
  char *data = kickAsteroid_data;
  //char pixel[3];  // moved in header
  //uint16_t title[128];  // moved in header
  for(k = 0; k < kickAsteroid_height; k++){
    for(i = 0; i < kickAsteroid_width; i++){
      KICK_ASTEROID(data, pixel);
      RGB565(pixel, &hexColor);
      title[i] = hexColor;
    }
    f3d_lcd_setAddrWindow (0,k,kickAsteroid_width-1,k,MADCTLGRAPHICS);
    f3d_lcd_pushColor(title,kickAsteroid_width);
  }
  
  int moved = 1; // 0 = no
  int pos = 0; // 0 = start for drawing and end for selecting
  int init = 1;
  while(1){
    // code here for selecting on menu
    //start();
    // move finger
    if(moved){
      if(pos){
	 // 106 is Start
	drawRect(0, 106, samFinger_width, samFinger_height, BLACK);
	data = samFinger_data;
	for(k = 0; k < samFinger_height; k++){
	  for(i = 0; i < samFinger_width; i++){
	    SAM_FINGER(data, pixel);
	    RGB565(pixel, &hexColor);
	    title[i] = hexColor;
	  }
	  // 123 is Instructions
	  f3d_lcd_setAddrWindow (0,k+123, samFinger_width,k+123,MADCTLGRAPHICS);
	  f3d_lcd_pushColor(title,samFinger_width);
	}
	pos = 0;
      }else{
	 // 123 is Instructions
	drawRect(0, 123, samFinger_width, samFinger_height, BLACK);
	data = samFinger_data;
	for(k = 0; k < samFinger_height; k++){
	  for(i = 0; i < samFinger_width; i++){
	    SAM_FINGER(data, pixel);
	    RGB565(pixel, &hexColor);
	    title[i] = hexColor;
	  }
	  // 106 is Start
	  f3d_lcd_setAddrWindow (0,k+106, samFinger_width,k+106,MADCTLGRAPHICS);
	  f3d_lcd_pushColor(title,samFinger_width);
	}
	pos = 1;
      }
      moved = 0;
      while (nunck.jy == 255 || nunck.jy == 0) {
	f3d_nunchuk_read(&nunck);
      }
    }else{
      f3d_nunchuk_read(&nunck);
      if(nunck.jy == 255 || nunck.jy == 0){
	moved = 1;
      }else if(nunck.c && !init) break; // exit loop, c button was pressed
      else init = 0;
    }
  }

  // ******* NOTE pos is flipped here  ********* //
  if(pos) start(); // start game
  else instructions(); // Instructions
}

void instructions(){
  f3d_lcd_fillScreen(BLACK);
  char *rules[] = {
    "Rule1",
    "RUle2",
    "rule3",
    "...",
    ""
  }; // set of fules
  int i = 0;
  
  f3d_lcd_drawString(5, 4, "Kick Asteroid", RED, BLACK);
  drawRect(0, 15, 128, 1, RED);
  while(**(rules + i)){
    f3d_lcd_drawString(5, 10*i + 35, *(rules + i), RED, BLACK);
    i++;
  } // draw each rule line by line, starting at line 5, each 5 from left
  struct nunchuk_data nunck;
  delay(100);
  nunck.c = 0;
  int init = 1;
  while(1){
    f3d_nunchuk_read(&nunck);
    // wait for c button to be pressed
    if(nunck.c && !init) break;
    init = 0;
  }
  splash(); // go back to splash
}

int play(){
  unsigned int retval;
  int bytesread;
  unsigned char * datapos = Scream_wav;

  struct ckhd hd;
  uint32_t waveid;
  struct fmtck fck;

  hd = readckhd2(datapos, &hd, 'FFIR');
  datapos += sizeof(struct ckhd);

  waveid = *((uint32_t * ) datapos);
  datapos += sizeof(waveid);
  if (waveid != 'EVAW')
    return -1;

  hd = readckhd2(datapos, &hd, ' tmf');
  datapos += sizeof(struct ckhd);

  fck = * ((struct fmtck * ) datapos);
  datapos += sizeof(fck);


  // now skip all non-data chunks !

  while (1) {
    hd = readckhd2(datapos, &hd, 0); //sets the next numbers for hd
    datapos += sizeof(struct ckhd); //moves the datapos position down a block
    if (hd.ckID == 'atad') //if they're equal to data string
      break;
    datapos += hd.cksize;   //if not move the pointer to whatever junk is in size
  }

  // Play it !

  memcpy(Audiobuf, datapos, AUDIOBUFSIZE / 2);
  datapos += AUDIOBUFSIZE / 2;
  hd.cksize -= AUDIOBUFSIZE / 2;
  audioplayerStart();
  while (hd.cksize) {
    int next = hd.cksize > AUDIOBUFSIZE / 2 ? AUDIOBUFSIZE / 2 : hd.cksize;
    if (audioplayerHalf) { // runs at beginning
      if (next < AUDIOBUFSIZE / 2){
        bzero(Audiobuf, AUDIOBUFSIZE / 2);
      }
      memcpy(Audiobuf, datapos, next);
      hd.cksize -= next;
      audioplayerHalf = 0;
      datapos += next;
    }
    if (audioplayerWhole) { // runs at end
      if (next < AUDIOBUFSIZE / 2){
        bzero( &Audiobuf[AUDIOBUFSIZE / 2], AUDIOBUFSIZE / 2);
      }
      memcpy( &Audiobuf[AUDIOBUFSIZE / 2], datapos, next);
      hd.cksize -= next;
      audioplayerWhole = 0;
      datapos += next;
    }
  }
  audioplayerStop();
  return 0;
}

struct ckhd readckhd2(unsigned char * data, struct ckhd * hd, uint32_t ckID) {
  hd = (struct ckhd * )data;
  if (ckID && (ckID != hd->ckID))
    exit(-1);
  return *hd;
}

int main(){
  /* setvbuf(stdin, NULL, _IONBF, 0); */
  /* setvbuf(stdout, NULL, _IONBF, 0); */
  /* setvbuf(stderr, NULL, _IONBF, 0); */
  f3d_timer2_init();
  f3d_dac_init();
  f3d_delay_init();
  f3d_rtc_init();
  f3d_systick_init();
  //f3d_uart_init();
  f3d_lcd_init();
  f3d_i2c1_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  f3d_accel_init();
  delay(10);
  f3d_mag_init();
  delay(10);
  
  STATE = NONGAME;
  // START GAME
  // boot();
  while(1) splash();
  return 0;
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t * file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif
/*  END main.c   */
