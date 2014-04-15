#include <Arduino.h>
#include "BBSensor.h"
#include "Subject.h"
#include "BBUtils.h"





BBSensor::BBSensor(){
	// Empty
	setDefaultRanges();	
}

BBSensor::BBSensor(SensorType sensorType):Subject(){
	_sensorType = sensorType;
	_avgPeriod = 1000;
	setDefaultRanges();	
}

BBSensor::BBSensor(SensorType sensorType, int pin):_pin(pin), Subject(){
	_sensorType = sensorType;
	_avgPeriod = 33;
	setDefaultRanges();	
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


// get scaled value from sensor
int BBSensor::read() {
	// int sensorValue = readSensor();
	int result = -1;
	
	int sensorValue = _runningTotal / _numReads;
	_runningTotal = 0;
	_numReads = 0;


	
	if (_sensorType == DIGITAL)
		return ( sensorValue == 0) ? result : 1; // 0 means off in digital sensor world
	

	if (sensorValue >= _inputRange[0] && sensorValue <= _inputRange[1]){
		result = scaleSensorValue(sensorValue);
	}



	return result;
}



bool BBSensor::isMotionDetected(){
	return read() > 0;
}


void BBSensor::setAveragingPeriod(int avgMillis){
	_avgPeriod = avgMillis;
}

void BBSensor::update(){
	// printf("update sensor");
	// static int _lastMillis;

	// printf("---------------");
	// printf("reading sensor: ");
	// print((int)this);
	// print(readSensor());
	// printf("---------------");

	_runningTotal += readSensor();
	++ _numReads;
	
	int elapsedMillis =  millis() - _lastMillis ;

	// printf("lastMillis");
	// print(_lastMillis);
	if(elapsedMillis > _avgPeriod){
	// 	printf("period elapsed");
	// 	print((int)this);
	// printf("-------------");


		notify();

		_lastMillis = millis();
	}

}


// **********************************************************
// Private
// **********************************************************

void BBSensor::setDefaultRanges(){
	setInputRange(200,550);
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

