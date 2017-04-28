//******************************************************************************************
//  File: PS_TMP75Temperature.cpp
//  Authors: Dan G Ogorchock, Prof. Mayhem 
//
//  Summary:  PS_TMP75Temperature is a class which implements the SmartThings "Temperature Measurement" 
//			  device capability.
//			  It inherits from the st::PollingSensor class.  The current version uses a digital input to measure the 
//			  temperature from a Texas Instruments TMP75 temperature sensor.    
//
//			  Create an instance of this class in your sketch's global variable section
//			  For Example:  st::PS_TMP75Temperature sensor1("temperature", 120, 3, TMP75_Address);
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

#include "PS_TMP75Temperature.h"

#include "Constants.h"
#include "Everything.h"
#include <Wire.h>
#include <TMP75.h>

namespace st
{
//private
	

//public
	//constructor - called in your sketch's global variable declaration section
	PS_TMP75Temperature::PS_TMP75Temperature(const __FlashStringHelper *name, unsigned int interval, int offset, int8_t Address):
		PollingSensor(name, interval, offset),
		m_dblTemperatureSensorValue(0.0),
		m_TMP75(TMP75(Address))
	{

	}
	
	//destructor
	PS_TMP75Temperature::~PS_TMP75Temperature()
	{
		
	}

	//SmartThings Shield data handler (receives configuration data from ST - polling interval, and adjusts on the fly)
	void PS_TMP75Temperature::beSmart(const String &str)
	{
		String s = str.substring(str.indexOf(' ') + 1);

		if (s.toInt() != 0) {
			st::PollingSensor::setInterval(s.toInt() * 1000);
			if (st::PollingSensor::debug) {
				Serial.print(F("PS_TMP75Temperature::beSmart set polling interval to "));
				Serial.println(s.toInt());
			}
		}
		else {
			if (st::PollingSensor::debug) 
			{
				Serial.print(F("TMP75Temperature::beSmart cannot convert "));
				Serial.print(s);
				Serial.println(F(" to an Integer."));
			}
		}
	}

	//initialization routine - get first set of readings and send to ST cloud
	void PS_TMP75Temperature::init()
	{		
		m_TMP75.begin();
		getData();
	}
	
	//function to get data from sensor and queue results for transfer to ST Cloud 
	void PS_TMP75Temperature::getData()
	{

		m_dblTemperatureSensorValue = m_TMP75.readFarenheit();
		if (isnan(m_dblTemperatureSensorValue))
		{
			if (st::PollingSensor::debug) {
				Serial.println(F("PS_TMP75Temperature:: Error Reading Temperature Sensor"));
			}
			m_dblTemperatureSensorValue = -99.0;
		}
		
		Everything::sendSmartString(getName() + " " + String(int(m_dblTemperatureSensorValue)));

	}
	
}