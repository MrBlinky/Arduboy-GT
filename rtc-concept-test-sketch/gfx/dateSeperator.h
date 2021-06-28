#pragma once
constexpr uint8_t dateSeperatorWidth = 4;
constexpr uint8_t dateSeperatorHeight = 16;

const uint8_t PROGMEM dateSeperator[] =
{
  dateSeperatorWidth, dateSeperatorHeight,
  //Frame 0
  0x00, 0x00, 0xE0, 0xE0, 
  0xF0, 0xFF, 0x1F, 0x01
};
