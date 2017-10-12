

#include <Arduino.h>
#include <U8g2lib.h>

#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

/*
  U8glib Example Overview:
    Frame Buffer Examples: clearBuffer/sendBuffer. Fast, but may not work with all Arduino boards because of RAM consumption
    Page Buffer Examples: firstPage/nextPage. Less RAM usage, should work with all Arduino boards.
    U8x8 Text Only Example: No RAM usage, direct communication with display controller. No graphics, 8x8 Text only.
    
*/

// Please UNCOMMENT one of the contructor lines below
// U8g2 Contructor List (Frame Buffer)
// The complete list is available here: https://github.com/olikraus/u8g2/wiki/u8g2setupcpp
// Please update the pin numbers according to your setup. Use U8X8_PIN_NONE if the reset pin is not connected

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);



void setup(void) {
  u8g2.begin();   //create screen object
}

void loop(void) {
  u8g2.clear();					// clear the internal memory
  //u8g2.clearDisplay();
  u8g2.setFont(u8g2_font_ncenB08_tr);	// choose a suitable font
  u8g2.drawStr(0,10,"Hello World!");	// write something to the internal memory
  
  int  randNumber = random(1000);   // create a random number between 0 and 999
  char buf[4];
  sprintf (buf, "%03d", randNumber);   // create a string 3 digits with leading zero if needed
  u8g2.drawStr(0, 22, buf);
  // u8g2.drawStr(0,30,randNumber);
  u8g2.drawBox(15,25,25,15);     // Draw a box (filled frame), starting at x/y position (upper left edge). The box has width w and height h.
 
  u8g2.sendBuffer();					// transfer internal memory to the display
  delay(1000);  
}

