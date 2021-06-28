// read DS3231 and FX data proof of concept test June 2021 by Mr. Blinky

// (Build with Arduboy Homemade package installed)

#include <Arduboy2.h> // include Arduboy2 library
#include <ArduboyFX.h>
#include <Sprites.h>
#include "ds3231.h"
#include "i2c.h"
#include "gfx/largeDigits.h"
#include "gfx/smallDigits.h"
#include "gfx/timeSeperator.h"
#include "gfx/dateSeperator.h"

Arduboy2 arduboy;
DS3231_time ds3231;

//assign values;
void setup() {
  arduboy.begin(); //initialisation with startup logo
  FX::disableOLED();
  FX::begin();

#if 0 //set date and time hack
  i2c_enable();
  i2c_start(SLAVE_ADDRESS_WRITE(DS3231_slaveAddress));
  i2c_write(DS3221_time_seconds);
  i2c_write(0x00);
  i2c_write(0x02);
  i2c_write(0x17);
  i2c_write(0x01);
  i2c_write(0x27);
  i2c_write(0x06);
  i2c_write(0x21);
  i2c_stop();
  i2c_disable();
 #endif
 
#if 0 //enable RTC hack
  i2c_enable();
  i2c_start(SLAVE_ADDRESS_WRITE(DS3231_slaveAddress));
  i2c_write(DS3221_control);
  i2c_write(0x04);
  i2c_stop();
  i2c_disable();
#endif
}

void loop() {
  if (!arduboy.nextFrame()) return; // Do nothing until it's time for the next frame

  //load FX loader screen graphic to display buffer
  FX::seekCommand(SFC_READ, (uint24_t)0x000100); //Flash address of Loader menu graphics
  SPDR = 0;
  FX::readBytesEnd(arduboy.sBuffer, WIDTH * HEIGHT / 8);

  //read DS3231 time
  i2c_enable();
  i2c_start(SLAVE_ADDRESS_WRITE(DS3231_slaveAddress));
  i2c_write(DS3221_time_seconds);
  i2c_stop();
  i2c_start(SLAVE_ADDRESS_READ(DS3231_slaveAddress ));
  //read directly into time structure
  uint8_t*p = (uint8_t*)&ds3231;
  for(uint8_t i = 0; i < (sizeof(ds3231) - 1); ++i) *p++ = i2c_readAck();
  *p = i2c_readNack(); // read last byte
  i2c_stop();
  i2c_disable();

  
  //display time
  Sprites::drawSelfMasked(119,24,smallDigits,ds3231.seconds >> 4);
  Sprites::drawSelfMasked(124,24,smallDigits,ds3231.seconds & 0x0F);
  Sprites::drawSelfMasked(102,16,timeSeperator,0);
  Sprites::drawSelfMasked(105,16,largeDigits,ds3231.minutes >> 4);
  Sprites::drawSelfMasked(112,16,largeDigits,ds3231.minutes & 0x0F);
  Sprites::drawSelfMasked(88,16,largeDigits,ds3231.hours >> 4);
  Sprites::drawSelfMasked(95,16,largeDigits,ds3231.hours & 0x0F);
  //display date
  Sprites::drawSelfMasked(26,16,largeDigits,ds3231.date >> 4);
  Sprites::drawSelfMasked(33,16,largeDigits,ds3231.date & 0x0F);
  Sprites::drawSelfMasked(21,16,dateSeperator,0);
  Sprites::drawSelfMasked( 7,16,largeDigits,ds3231.month >> 4);
  Sprites::drawSelfMasked(14,16,largeDigits,ds3231.month & 0x0F);
  
  FX::enableOLED();
  arduboy.display(CLEAR_BUFFER); //clears display after displaying display buffer
  FX::disableOLED();
}
