#include <Arduino.h>
#include "BBSensor.h"
#include "ISubject.h"
#include "BBUtils.h"







BBSensor::BBSensor(int pin, SensorType type):
	_pin(pin),
	_sensorType(type)
{

}



// **********************************************************
// Static
// **********************************************************

void BBSensor::syncronize(byte pin, int ping, long unsigned rest){
	LOGS("sync sensor");
	digitalWrite(pin, HIGH);
	delayMicroseconds(ping);
	digitalWrite(pin, LOW);
	delay(rest);
}







// **********************************************************
// Public API
// **********************************************************


void BBSensor::begin(){
	// if (_sensorType == DIGITAL)
		// pinMode(_pin, INPUT);
	// LOGS("BASE SENSOR BEGIN");
	_rollingAverage = 0;
	_runningTotal = 0;
	for(int i=0; i<DEFAULT_SMOOTHING; i++){
		_readings[i] = 0;
	}
	
}

void BBSensor::invertOutput(bool invert){
	_invertOutput = invert;
}

void BBSensor::setPin(int pin){
	_pin = pin;
	// begin();
}
int BBSensor::getPin(){
	return _pin;
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

void BBSensor::setSmoothingFactor(int smoothing){
	_smoothingFactor = DEFAULT_SMOOTHING;
}
// get scaled value from sensor
int BBSensor::read() {

	int result = -1;
	int sensorValue = _rollingAverage;


	// TODO: implement this in the subclass for PIRSensor
	if (_sensorType == PIR){
		return ( sensorValue == 0) ? result : 1; // 0 means off in digital sensor world
	}
	
	if (sensorValue >= _inputRange[0] && sensorValue <= _inputRange[1]){
		result = scaleSensorValue(sensorValue);
		if (_invertOutput)
			result = abs(result - _outputRange[1]);
	}

	return result;
}

void BBSensor::update(){
	
	// CALCULATE ROLLING AVERAGE


	_runningTotal = _runningTotal - _readings[_currentIndex];

	_readings[_currentIndex] = readSensor();

	_runningTotal = _runningTotal + _readings[_currentIndex];
	// LOGS("_rollingAverage");
	// Serial.LOG("AVERAGE: ");
	// Serial.println(F("AVERAGE: "));
	// Serial.println(_readings[_currentIndex]);
	// LOG(_readings[_currentIndex]);
	// LOG(_runningTotal);
	// LOG(_currentIndex);
	_currentIndex++;
	_currentIndex = _currentIndex % DEFAULT_SMOOTHING;

	_rollingAverage = _runningTotal / DEFAULT_SMOOTHING; // TODO: move this to read method
	// LOG(_rollingAverage);
	// Serial.println(_rollingAverage);
	// LOG(_rollingAverage);
	// TEST UPDATE TIME

	// int elapsedMillis =  millis() - _lastMillis ;

	// if(elapsedMillis > _updateInterval){
	// 	notify();
	// 	_lastMillis = millis();
	// }
	notify();
}


// **********************************************************
// Private
// **********************************************************

int BBSensor::readSensor(){
	return 0;
}

int BBSensor::scaleSensorValue(int value){
	float scale = (float)(_inputRange[1] - _inputRange[0]) / (float)(_outputRange[1]- _outputRange[0]);
	float offset = (float)_inputRange[0];
	int result = floor((value - offset) / scale);
	return result;
 }

