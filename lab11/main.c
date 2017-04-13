/******************************************
 *
 *
 *   File: main.c
 *   Author: Michael McCann- mimccann
 *   Partner: Samuel Carter: sambcart
 *   School: Indiana University
 *   Assignment: lab 11
 *   Part of: labs
 *   Description: Plays sounds, displays options on screen
 *   Date Created: 04/06/2017
 *   Date Modified: 04/13/2017
 *   Modified By: Michael McCann
 *
 *   Revision Description:  Changed comment block
 */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers 
#include <f3d_led.h> // Pull in include file for the local drivers
#include <f3d_uart.h> 
#include <f3d_i2c.h> 
#include <f3d_rtc.h> 
#include <f3d_systick.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <f3d_lcd_sd.h>
#include <f3d_nunchuk.h>

#define TIMER 20000
#define AUDIOBUFSIZE 128
int play(int);
extern uint8_t Audiobuf[AUDIOBUFSIZE];
extern int audioplayerHalf;
extern int audioplayerWhole;

extern unsigned char chirp_16_wav[];
extern unsigned char alarm_16_wav[];

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


int main(void) {



  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  f3d_timer2_init();
  f3d_dac_init();
  f3d_delay_init();
  f3d_rtc_init();
  f3d_systick_init();
  f3d_uart_init();
  f3d_lcd_init();
  f3d_i2c1_init();
  delay(10);
  f3d_nunchuk_init();
  delay(10);
  
  int played = 0;
  int file = 0;
  struct nunchuk_data nunck;
  // uses DMA
  f3d_lcd_fillScreen2(WHITE);
  f3d_lcd_drawString(2,0, "Choose file in red.", BLACK, WHITE);
  f3d_lcd_drawString(10,20, "chirp.wav", BLACK,WHITE);
  f3d_lcd_drawString(10, 10, "Alarm.wav", RED, WHITE);
  f3d_lcd_drawString(2,30, "Press \"c\" to play.", BLACK, WHITE);
  while (1){
    if(!played){
      play(file);
      played = 1; // played
    }
    else{
      f3d_nunchuk_read(&nunck);
      if(nunck.jy == 255 || nunck.jy == 0){
	file = (file + 1) % 2;
	if(file){
	  f3d_lcd_drawString(10,20, "chirp.wav", RED,WHITE);
	  f3d_lcd_drawString(10, 10, "Alarm.wav", BLACK, WHITE);
	}else{
	  f3d_lcd_drawString(10,20, "chirp.wav", BLACK,WHITE);
	  f3d_lcd_drawString(10, 10, "Alarm.wav", RED, WHITE);
	}
      }
      if(nunck.c)
	  played = 0;
      delay(100);
    }
  }
}

int play(int i){
  unsigned int retval;
  int bytesread;
  unsigned char * datapos = chirp_16_wav;
  if(!i) datapos = alarm_16_wav; 
  printf("Reset\n");

  struct ckhd hd;
  uint32_t waveid;
  struct fmtck fck;

  printf("reading RIFF section... \n");
  hd = readckhd2(datapos, &hd, 'FFIR');
  datapos += sizeof(struct ckhd);

  printf("reading WAVE section... \n");
  waveid = *((uint32_t * ) datapos);
  datapos += sizeof(waveid);
  if (waveid != 'EVAW')
    return -1;

  printf("reading fmt section... \n");
  hd = readckhd2(datapos, &hd, ' tmf');
  datapos += sizeof(struct ckhd);

  printf("reading wav info section... \n");
  fck = * ((struct fmtck * ) datapos);
  datapos += sizeof(fck);

  printf("audio format 0x%x\n", fck.wFormatTag);
  printf("channels %d\n", fck.nChannels);
  printf("sample rate %d\n", fck.nSamplesPerSec);
  printf("data rate %d\n", fck.nAvgBytesPerSec);
  printf("block alignment %d\n", fck.nBlockAlign);
  printf("bits per sample %d\n", fck.wBitsPerSample);

  // now skip all non-data chunks !

  while (1) {
    hd = readckhd2(datapos, &hd, 0); //sets the next numbers for hd
    datapos += sizeof(struct ckhd); //moves the datapos position down a block
    if (hd.ckID == 'atad') //if they're equal to data string
      break;
    datapos += hd.cksize;   //if not move the pointer to whatever junk is in size
  }

  printf("Samples %d\n", hd.cksize);

  // Play it !

  memcpy(Audiobuf, datapos, AUDIOBUFSIZE / 2);
  datapos += AUDIOBUFSIZE / 2;
  hd.cksize -= AUDIOBUFSIZE / 2;
  //printf("%x\n", *datapos);
  audioplayerStart();
  while (hd.cksize) {
    int next = hd.cksize > AUDIOBUFSIZE / 2 ? AUDIOBUFSIZE / 2 : hd.cksize;
    if (audioplayerHalf) { // runs at beginning
      //printf("Half %x\n", *datapos);
      if (next < AUDIOBUFSIZE / 2){
	printf("Half bzero\n");
        bzero(Audiobuf, AUDIOBUFSIZE / 2);
      }
      memcpy(Audiobuf, datapos, next);
      hd.cksize -= next;
      audioplayerHalf = 0;
      datapos += next;
    }
    if (audioplayerWhole) { // runs at end
      //printf("Whole %x\n", *datapos);
      if (next < AUDIOBUFSIZE / 2){
	printf("Whole bzero\n");
        bzero( &Audiobuf[AUDIOBUFSIZE / 2], AUDIOBUFSIZE / 2);
      }
      memcpy( &Audiobuf[AUDIOBUFSIZE / 2], datapos, next);
      hd.cksize -= next;
      audioplayerWhole = 0;
      datapos += next;
    }
    //
    //printf("Playing... %d", hd.cksize);
  }
  audioplayerStop();

  printf("\nClose the file.\n");
  return 0;
}

struct ckhd readckhd2(unsigned char * data, struct ckhd * hd, uint32_t ckID) {
  hd = (struct ckhd * )data;
  printf("ckID: %x\n",ckID);
  printf("hd->ckID: %x\n", hd->ckID);
  printf("cksize: %i\n",hd->cksize);
  if (ckID && (ckID != hd->ckID))
    exit(-1);
  return *hd;
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t * file, uint32_t line) {
  /* Infinite loop */
  /* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
