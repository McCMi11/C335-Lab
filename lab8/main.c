//Name: Michael McCann
//Username: mimccann
// Partner: Connor Ward
// username: conward
// No partner

/* main.c ---
*
* Filename: main.c
* Description:
* Author:
* Maintainer:
* Created: Thu Jan 10 11:23:43 2013
/* Code: */

#include <stm32f30x.h> // Pull in include files for F30x standard drivers
#include <f3d_uart.h>
#include <f3d_user_btn.h>
#include <f3d_lcd_sd.h>
#include <f3d_i2c.h>
#include <f3d_gyro.h>
#include <f3d_accel.h>
#include <f3d_mag.h>
#include <f3d_led.h>
#include <stdio.h>
#include <math.h>
#include <f3d_nunchuk.h>

#define TIMER 20000

void drawVertLine(uint8_t x, uint8_t y, int length, int c){
  int i = 0;
  if (length > 0) {
    while (i < length) {
      f3d_lcd_drawPixel(x,y-i,c);
      i = i+1;
    }
  } else {
    while(i < (-1*length)) {
      f3d_lcd_drawPixel(x,y+i,c);
      i=i+1;
    }
  }
}

void drawVertBar(uint8_t x, uint8_t y, int length, int width, int c){
  int j = 0;
  while (j < width) {
    drawVertLine(x+j,y,length, c);
    j=j+1;
  }
}

void drawMiddleLine(int y) {
  int i = 0;
  while (i <= 127) {
    // colors the pixel blue at (i,y)
    // and then increments i
    f3d_lcd_drawPixel(i++,y,BLUE);
  }
}

int main(void) {
   setvbuf(stdin, NULL, _IONBF, 0);
   setvbuf(stdout, NULL, _IONBF, 0);
   setvbuf(stderr, NULL, _IONBF, 0);

  // Set up your inits before you go ahead

   f3d_uart_init();
   f3d_lcd_init();
   f3d_led_init();
   f3d_user_btn_init();
   f3d_gyro_init();

   //initialize with delays
   f3d_i2c1_init();
   delay(10);
   f3d_accel_init();
   delay(10);
   f3d_mag_init();
   delay(10);
   f3d_nunchuk_init();
   delay(10);

   //create floats for the accel, mag, and gyro
   float a[3];
   float m[3];
   float i[3];

   //create floats for the compass computations
   float pitch, roll, heading, xh, yh, degrees;
   float pitchnun, rollnun;

   //create ints for various loops and calls throughout
   int j, k;
   int x, y, xnun, ynun;
   int button = 0;

   char output1[10]; //string for snprintf() to use
   char output2[10]; //string for snprintf() to use
   char output3[10]; //string for snprintf() to use

   struct nunchuk_data test;

   //establish a blank white screen on LCD
   f3d_lcd_fillScreen(WHITE);

   while(1) {
     if(button == 2 || button == 0){
       for(j = 20; j < 110; j++) {
	 f3d_lcd_drawPixel(j, 80, BLACK);
       }
       for(j = 20; j < 150; j++) {
	 f3d_lcd_drawPixel(60, j, BLACK);
       }

       f3d_lcd_drawChar(10, 78, 'R', BLACK, WHITE);
       f3d_lcd_drawChar(58, 10, 'P', BLACK, WHITE);
     }
     f3d_nunchuk_read(&test);

     if(button == 2) {

       //Draw title
       f3d_lcd_drawString(5, 0, "Nunchuck", RED, WHITE);
       //Remove point on graph
       f3d_lcd_drawChar(xnun, ynun, '=', WHITE, WHITE);
      
       
       //calculate pitch and roll for the nunchuk
       pitchnun = atan(test.ax/sqrt((test.ay * test.ay)) + ((test.az * test.az)));
       rollnun = atan(test.ay/sqrt((test.ax * test.ax) + (test.az * test.az)));
       
       //adjust roll pitch for displaying on graph
       rollnun = rollnun * 100;
       pitchnun = pitchnun * 1000; 

       xnun =  rollnun ;
       ynun =  pitchnun + 40;

       //graph roll and pitch using an equal sign
       f3d_lcd_drawChar(xnun, ynun, '=', BLACK, WHITE);
   
       //test readout from nunchuk
       /*
	 printf("jx: %d\n", test.jx);// left = 0, right = 255
	 printf("jy: %d\n", test.jy);// down = 0, up = 255
	 printf("ax: %d\n", test.ax);// 
	 printf("ay: %d\n", test.ay);//  
	 printf("az: %d\n", test.az);//
	 printf("c: %d\n", test.c);// 1=pressed, 0= not
	 printf("z: %d\n\n\n", test.z);// same as test.c
       */
     }
       
     f3d_accel_read(a);
     f3d_mag_read(m);

     //calculate pitch and roll
     pitch = atan(a[0]/sqrt(((a[1]) * (a[1])) + ((a[2]) * (a[2]))));
     roll = atan(a[1]/sqrt(((a[0]) * (a[0])) + ((a[2]) * (a[2]))));

     //calculate xh and yh
     xh = (m[0] * cos(pitch)) + (m[2] * sin(pitch));
     yh = (m[0]*sin(roll)*sin(pitch))+(m[1]*cos(roll))-(m[2]*sin(roll)*cos(pitch));  

     //combine xh and yh to get heading
     heading = atan(yh/xh);

     //convert heading to degrees
     degrees = (heading * 180) / 3.14159265;

     //if button int = 1, display the compass
     if(button == 1) {

       //light LED that corresponds to the direction the board is pointed
       f3d_lcd_drawString(5, 0, "See LED", RED, WHITE);
       if(xh < 0 && degrees > 0) {
	 f3d_led_all_off();  
	 f3d_led_on(1);
       }
       if(xh < 0 && degrees < 0) {
	 f3d_led_all_off();
	 f3d_led_on(1);
       }
       if(xh < 0 && degrees > 22.5) {
	 f3d_led_all_off();
	 f3d_led_on(2);
       }  
       if(xh < 0 && degrees > 67.5) {
	 f3d_led_all_off();
	 f3d_led_on(3);
       }
       if(xh > 0 && degrees < -67.5) {
	 f3d_led_all_off();
	 f3d_led_on(3);
       }
       if(xh > 0 && degrees < -22.5) {
	 f3d_led_all_off();
	 f3d_led_on(4);
       } 
       if(xh > 0 && degrees > -22.5) {
	 f3d_led_all_off();
	 f3d_led_on(5);
       }
       if(xh > 0 && degrees > 0) {
	 f3d_led_all_off();
	 f3d_led_on(5);
       }
       if(xh > 0 && degrees > 22.5) {
	 f3d_led_all_off();
	 f3d_led_on(6);
       }
       if(xh > 0 && degrees > 67.5) {
	 f3d_led_all_off();
	 f3d_led_on(7);
       }
       if(xh < 0 && degrees < -67.5) {
	 f3d_led_all_off();
	 f3d_led_on(7);
       }
       if(xh < 0 && degrees < -22.5) {
	 f3d_led_all_off();
	 f3d_led_on(0);
       }
     }
     
     //if button is pressed again
     if(button == 0) {

       //Draw title
       f3d_lcd_drawString(5, 0, "Accel/Mag", RED, WHITE);
       
       roll = roll * 100;
       pitch = pitch * 100;
       f3d_lcd_drawChar(x, y, '=', WHITE, WHITE);
       x = 65 + roll;
       y = 85 + pitch;

       //graph roll and pitch using an equal sign
       f3d_lcd_drawChar(x, y, '=', BLACK, WHITE);
     }

     if(button == 3) {
       f3d_lcd_drawString(5, 0, "Gyro", RED, WHITE);
       //draw X line
       drawVertBar(7,90,(int) i[0]/10,6, WHITE);//divide by 10 so it fits on the screen

       //draw Y line
       drawVertBar(61,90,(int) i[1]/10,6, WHITE);

       //draw Z line
       drawVertBar(114,90,(int) i[2]/6,6, WHITE);
       
       f3d_gyro_getdata(i);
       //f3d_lcd_fillScreen(WHITE);
       drawMiddleLine(90); //draw the diving line at y=90

       //display X value
       snprintf(output1, 10, "%f", i[0]);
       f3d_lcd_drawString(20,10,"X: ",RED,WHITE);
       f3d_lcd_drawString(35,10,output1,RED,WHITE);

       //display Y value
       snprintf(output2, 10, "%f", i[1]);
       f3d_lcd_drawString(20,20,"Y: ",BLUE,WHITE);
       f3d_lcd_drawString(35,20,output2,BLUE,WHITE);

       //display Z value
       snprintf(output3, 10, "%f", i[2]);
       f3d_lcd_drawString(20,30,"Z: ",GREEN,WHITE);
       f3d_lcd_drawString(35,30,output3,GREEN,WHITE);
    
       //draw X line
       drawVertBar(7,90,(int) i[0]/10,6, RED);//divide by 10 so it fits on the screen

       //draw Y line
       drawVertBar(61,90,(int) i[1]/10,6, BLUE);

       //draw Z line
       drawVertBar(114,90,(int) i[2]/6,6, GREEN);

     }

     //changes the variable that controls which display is activated
     if(user_btn_read() || test.c || test.jx == 255) {
       button++;
       button = button%4;
       f3d_led_all_off();
       f3d_lcd_fillScreen(WHITE);
     }

     //goes in opposite direction
     else if(test.z || !test.jx){
       button--;
       if(button < 0){
	 button = 3;
       }
       else {
	 button = button%4;
       }
       f3d_led_all_off();
       f3d_lcd_fillScreen(WHITE);
     }
   }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line) {
/* Infinite loop */
/* Use GDB to find out why we're here */
  while (1);
}
#endif

/* main.c ends here */
