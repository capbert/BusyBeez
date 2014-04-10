#include <Arduino.h>
#include "BBSensor.h"


BBSensor::BBSensor(){
	// Empty
}

BBSensor::BBSensor(SensorType sensorType){
	_sensorType = sensorType;
}

// BBSensor::BBSensor(int pin, SensorType sensorType){
	
// 	_sensorType = sensorType;
// 	_pin = pin;

// 	// if (sensorType == DIGITAL)
// 	pinMode(_pin, INPUT);

// 	setDefaultRanges();
// }

// **********************************************************
// Public API
// **********************************************************

void BBSensor::setPin(int pin){
	_pin = pin;
	if (_sensorType == DIGITAL)
		pinMode(_pin, INPUT);
	setDefaultRanges();
}

/*
	Set the range of values from attached sensor that you wish to respond to
	Default: low=0 high=1024
*/
void BBSensor::setInputRange(int low, int high){
	_inputRange[0] = low;
	_inputRange[1] = high;
}


/*
	Set the range of values you wish to receive from this wrapper
	Default: low=0 high=127
*/
void BBSensor::setOutputRange(int low, int high){
	_outputRange[0] = low;
	_outputRange[1] = high;
}


// get scaled value from sensor
int BBSensor::read() {
	int sensorValue = readSensor();
	int result = -1;
	
	
	if (_sensorType == DIGITAL)
		return ( sensorValue == 0) ? result : 1; // 0 means off in digital sensor world
	

	if (sensorValue >= _inputRange[0] && sensorValue <= _inputRange[1]){
		result = scaleSensorValue(sensorValue);
	}

	// Serial.print("TYPE =");
	// Serial.println(_sensorType);

	// if( _sensorType ==  ANALOG){
	
	// 	Serial.println(F("read ANALOG sensor value: "));

	// }else{
		
	// 	Serial.println(F("read DIGITAL sensor value: "));
	// }

	// Serial.println(result);

	return result;
}


bool BBSensor::isMotionDetected(){
	return read() > 0;
}

// **********************************************************
// Private
// **********************************************************

void BBSensor::setDefaultRanges(){
	_inputRange[0] = 200;
	_inputRange[1] = 550;
	_outputRange[0] = 0;
	_outputRange[1] = 127;
}

int BBSensor::readSensor(){
	
	// debugging stub -----------------
	// static int count = 0;
	// int value;
	// if(count > 10){
	// 	count = 0;
	// 	value = 0;
	// }else{
	// 	value = 1;
	// }
	// count ++;

	// return value;
	// end stub -------------------


	return _sensorType == ANALOG ? analogRead(_pin) : digitalRead(_pin);
}

int BBSensor::scaleSensorValue(int value){
	float scale = (float)(_inputRange[1] - _inputRange[0]) / (float)(_outputRange[1]- _outputRange[0]);
	float offset = (float)_inputRange[0];
	int result = floor((value - offset) / scale);
	return result;
 }

