#include <Arduino.h>
#include "BBSensor.h"
#include "ISubject.h"
#include "BBUtils.h"





// BBSensor::BBSensor(){
// 	// Empty
// 	setDefaultRanges();	
// }

// BBSensor::BBSensor(SensorType sensorType){
// 	_sensorType = sensorType;
// 	_updateInterval = DEFAULT_UPDATE_INTERVAL;
// 	setDefaultRanges();	
// 	setSmoothingFactor();
// }

BBSensor::BBSensor(SensorType sensorType, int pin, bool invert):
	_pin(pin), 
	_invertOutput(invert)
{
	_sensorType = sensorType;
	_updateInterval = DEFAULT_UPDATE_INTERVAL;
	// zeroReadingsArray()

	_currentIndex = 0;
	_runningTotal = 0;
	_rollingAverage = 0;




	setDefaultRanges();	
	setSmoothingFactor();
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


void BBSensor::begin(){
	if (_sensorType == DIGITAL)
		pinMode(_pin, INPUT);

	for(int i=0; i<_smoothingFactor; i++){
		_readings[i] = 0;
	}
	
}

void BBSensor::setPin(int pin){
	_pin = pin;
	// begin();
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
	_smoothingFactor = smoothing;
}
// get scaled value from sensor
int BBSensor::read() {

	int result = -1;
	int sensorValue = _rollingAverage;
	
	if (_sensorType == DIGITAL)
		return ( sensorValue == 0) ? result : 1; // 0 means off in digital sensor world
	
	if (sensorValue >= _inputRange[0] && sensorValue <= _inputRange[1]){
		result = scaleSensorValue(sensorValue);
		if (_invertOutput)
			result = abs(result - _outputRange[1]);
	}

	return result;
}



bool BBSensor::isMotionDetected(){
	return read() > 0;
}


void BBSensor::setAveragingPeriod(int avgMillis){
	_updateInterval = avgMillis;
}

void BBSensor::update(){
	
	// CALCULATE ROLLING AVERAGE



	_runningTotal = _runningTotal - _readings[_currentIndex];

	_readings[_currentIndex] = readSensor();

	_runningTotal = _runningTotal + _readings[_currentIndex];

	// printf("_rollingAverage");
	// print(_readings[_currentIndex]);
	// print(_runningTotal);
	// print(_currentIndex);
	_currentIndex++;
	_currentIndex = _currentIndex % _smoothingFactor;

	_rollingAverage = _runningTotal / _smoothingFactor;
	// print(_rollingAverage);
	// TEST UPDATE TIME

	int elapsedMillis =  millis() - _lastMillis ;

	if(elapsedMillis > _updateInterval){
		notify();
		_lastMillis = millis();
	}

}


// **********************************************************
// Private
// **********************************************************

void BBSensor::setDefaultRanges(){
	setInputRange(100,550);
	setOutputRange(0,127);
	// _inputRange[0] = 200;
	// _inputRange[1] = 550;
	// _outputRange[0] = 0;
	// _outputRange[1] = 127;
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

