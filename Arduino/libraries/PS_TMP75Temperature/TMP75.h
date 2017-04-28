/*************************************************** 
  This is a library for the Texas Instruments TMP75 Sensor
  These sensors use I2C to communicate, 3 pins are required to  
  interface

  Written by Prof. Mayhem for Yoyodyne Monkey Works, Inc.
 ****************************************************/

#ifndef TMP75_H
#define TMP75_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include "PollingSensor.h"

class TMP75 {
 public:
  TMP75(int8_t _address);

  void begin(void);
  double readCelsius(void);
  double readFarenheit(void);

 private:
  boolean initialized;

  int8_t address;
};

#endif