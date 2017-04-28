//******************************************************************************************
//  File: PS_TMP75Temperature.h
//  Authors: Dan G Ogorchock, Prof. Mayhem
//
//  Summary:  PS_TMP75Temperature is a class which implements the SmartThings "Temperature Measurement" 
//			  device capability.
//			  It inherits from the st::PollingSensor class.  The current version uses a digital input to measure the 
//			  temperature from a Texas Instruments TMP75 temperature sensor.
//
//			  Create an instance of this class in your sketch's global variable section
//			  For Example:  st::PS_TMP75Temperature sensor1("temperature", 120, 3, PIN_SCLK, PIN_CS, PIN_MISO);
//
//			  st::PS_TMP75Temperature() constructor requires the following arguments
//				- String &name - REQUIRED - the name of the object - must match the Groovy ST_Anything DeviceType tile name
//				- long interval - REQUIRED - the polling interval in seconds
//				- long offset - REQUIRED - the polling interval offset in seconds - used to prevent all polling sensors from executing at the same time
//				- int8_t pinSCLK - REQUIRED - the Arduino Pin to be used as the TMP75 SCLK
//				- int8_t pinCS - REQUIRED - the Arduino Pin to be used as the TMP75 CS
//				- int8_t pinMISO - REQUIRED - the Arduino Pin to be used as the TMP75 MISO
//
//			  This class supports receiving configuration data from the SmartThings cloud via the ST App.  A user preference
//			  can be configured in your phone's ST App, and then the "Configure" tile will send the data for all sensors to 
//			  the ST Shield.  For PollingSensors, this data is handled in the beSMart() function.
//
//			  TODO:  Determine a method to persist the ST Cloud's Polling Interval data
//
//  Change History:
//
//    Date        Who            What
//    ----        ---            ----
//    2017-04-25  Prof. Mayhem   Original Creation
//
//
//******************************************************************************************

#ifndef ST_PS_TMP75TEMPERATURE_H
#define ST_PS_TMP75TEMPERATURE_H

#include "PollingSensor.h"
#include <SPI.h>
#include <TMP75.h>

namespace st
{
	class PS_TMP75Temperature: public PollingSensor
	{
		private:
			double m_dblTemperatureSensorValue;		//current Temperature value
			TMP75 m_TMP75;	//TMP75 object

		public:

			//constructor - called in your sketch's global variable declaration section
			PS_TMP75Temperature(const __FlashStringHelper *name, unsigned int interval, int offset, int8_t address);
			
			//destructor
			virtual ~PS_TMP75Temperature();

			//SmartThings Shield data handler (receives configuration data from ST - polling interval, and adjusts on the fly)
			virtual void beSmart(const String &str);
			
			//initialization routine
			virtual void init();

			//function to get data from sensor and queue results for transfer to ST Cloud 
			virtual void getData();
			
			//gets
			inline int getTemperatureSensorValue() const { return int(m_dblTemperatureSensorValue); }
				
			//sets
	
	};
}



#endif