/*************************************************** 
  This is a library for the Texas Instruments TMP75 Sensor
  These sensors use I2C to communicate, 3 pins are required to  
  interface

  Written by Prof. Mayhem for Yoyodyne Monkey Works, Inc.
 ****************************************************/

#include "TMP75.h"
#ifdef __AVR
  #include <avr/pgmspace.h>
#elif defined(ESP8266)
  #include <pgmspace.h>
#endif

#include <stdlib.h>
#include <Wire.h>

TMP75::TMP75(int8_t _address) {
  address = _address;

  initialized = false;
}

void TMP75::begin(void) {
	Wire.begin();                                // Join the I2C bus as a master
  Wire.beginTransmission(address);             // Address the TMP75 sensor
  Wire.write(0x01);                            // Address the Configuration register 
  Wire.write(0x60);                            // Set the temperature resolution 
  Wire.endTransmission();                      // Stop transmitting
  Wire.beginTransmission(address);             // Address the TMP75 sensor
  Wire.write(0x00);                            // Address the Temperature register 
  Wire.endTransmission();                      // Stop transmitting
  initialized = true;
}

double TMP75::readCelsius(void) {
	Wire.requestFrom(address,2);                 // Address the TMP75 and set number of bytes to receive
  byte MostSigByte = Wire.read();              // Read the first byte this is the MSB
  byte LeastSigByte = Wire.read();             // Now Read the second byte this is the LSB

  // Being a 12 bit integer use 2's compliment for negative temperature values
  int TempSum = (((MostSigByte << 8) | LeastSigByte) >> 4); 
  // From Datasheet the TMP75 has a quantisation value of 0.0625 degreesC per bit
  float centigrade = (TempSum*0.0625);

	if (st::PollingSensor::debug) {
		Serial.print(F("TMP75 Address: "));
		Serial.print("0x");
		Serial.println(address,HEX);
	  
    Serial.print("0x"); Serial.println(MostSigByte, HEX);
    Serial.print("0x"); Serial.println(LeastSigByte, HEX);
    Serial.print(F("\tTemp: ")); Serial.println(centigrade);
  }
  return centigrade;
}

double TMP75::readFarenheit(void) {
  return readCelsius()*1.8+32;;
}
