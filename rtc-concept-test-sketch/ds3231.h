#pragma once

// DS3231 lite library WIP

// DS3231 registers
constexpr uint8_t DS3231_slaveAddress = 0x68; //DS3231 I2C slave address
constexpr uint8_t DS3221_time_seconds = 0x00; // bcd seconds
constexpr uint8_t DS3221_time_minutes = 0x01; // bcd minutes
constexpr uint8_t DS3221_time_hours   = 0x02; // bit 6 clear = 24 hour mode: bit 5..0 BSD hours, bit 6 set = 12 hour mode: bit 5 clear: AM, set: PM, bits 4..0 bcd hours
constexpr uint8_t DS3221_time_day     = 0x03; // bits 2..0 day
constexpr uint8_t DS3221_time_date    = 0x04; // bcd date
constexpr uint8_t DS3221_time_month   = 0x05; // bit 7: century, bits 6..0 bcd month
constexpr uint8_t DS3221_time_year    = 0x06; // bcd year

constexpr uint8_t DS3221_control      = 0x0E; // Control register

struct DS3231_time
{
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t day;
  uint8_t date;
  uint8_t month;
  uint8_t year;
};

struct DS3231_alarm1
{
  uint8_t seconds;
  uint8_t minutes;
  uint8_t hours;
  uint8_t day;
};

struct DS3231_alarm2
{
  uint8_t minutes;
  uint8_t hours;
  uint8_t day;
};

struct DS3231_data
{
  DS3231_time time;
  DS3231_alarm1 alarm1;
  DS3231_alarm2 alarm2;
  uint8_t control;
  uint8_t controlStatus;
  uint8_t temp_MSB;
  uint8_t temp_LSB;
};
