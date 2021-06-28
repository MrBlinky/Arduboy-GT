#pragma once

//I2C lite library for Arduboy

//Macros
#define SLAVE_ADDRESS_WRITE(a) ((a << 1) | 0)
#define SLAVE_ADDRESS_READ(a)  ((a << 1) | 1)

#define I2C_SPEED 400000L // 400Kbps bitrate

//I2C pins
#define I2C_PORT  PORTD
#define I2C_DDR   DDRD
#define I2C_PIN   PIND
#define I2C_SCL   PORTD0
#define I2C_SDA   PORTD1

void i2c_wait()
{
  while (!(TWCR & _BV(TWINT)));  
}

void i2c_enable()
{
  PRR0 &= ~_BV(PRTWI);                   // disable TWI power reduction (enabled by Arduboy2 library)
  PORTD |= _BV(I2C_SDA);                 // pullups / inactive SDA flashchipselect
  PORTD |= _BV(I2C_SCL);
  DDRD  |= _BV(I2C_SDA);                 // outputs (irrellevant until TWI enabled)
  DDRD  |= _BV(I2C_SCL);
  TWSR  &= ~(_BV(TWPS1) | _BV(TWPS0));   // set I2C prescaler
  TWBR = ((F_CPU / I2C_SPEED) - 16) / 2; // configure bitrate
  //TWCR = _BV(TWEN) | _BV(TWEA);          // enable TWI and change pin function, enable ACKs
}

void i2c_disable()
{
  TWCR = 0;           // disable TWI and restore normal pin function (SDA and SCL become active high outputs)
  PRR0 |= _BV(PRTWI); // enable TWI power reduction
}

void i2c_write(uint8_t data)
{
  TWDR = data;
  TWCR = _BV(TWINT) | _BV(TWEN);              // start transmission of data
  i2c_wait();                                 // wait for data to be transmitted  
}

void i2c_start(uint8_t slaveAddrReadWrite)
{
  TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN); // send start condition
  i2c_wait();                                 // wait for start condition to be transmitted  
  i2c_write(slaveAddrReadWrite);
}

void i2c_stop()
{
  TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN); // send stop condition
}

uint8_t i2c_readAck(void)
{
  TWCR = _BV(TWINT)|_BV(TWEN)|_BV(TWEA); 
  i2c_wait();
  return TWDR;
}

uint8_t i2c_readNack(void)  // used for reading last byte
{
  TWCR = _BV(TWINT)|_BV(TWEN);
  i2c_wait();
  return TWDR;
}
