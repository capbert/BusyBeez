#ifndef BBSensor_h
#define BBSensor_h

#include "Subject.h"

class BBSensor : public Subject
{
public:
	
	enum SensorType {
		ANALOG, 
		DIGITAL
	};

	BBSensor();
	BBSensor(SensorType);
	BBSensor(SensorType, int pin);
	// BBSensor(SensorType, int resolution);
	void begin();
	void setPin(int pin);
	void setInputRange(int low, int high);
	void setOutputRange(int low, int high);
	void setAveragingPeriod(int avgMillis);
	int read();
	void update();
	bool isMotionDetected();

private:
	int _pin;
	int _sensorType;
	int _inputRange[2];
	int _outputRange[2];
	
	// averaging
	int _updateInterval;
	
	static const int NUMBER_OF_READINGS = 10;
	static const int DEFAULT_UPDATE_INTERVAL = 50;
	int _readings[NUMBER_OF_READINGS];
	int _runningTotal;
	int _rollingAverage;
	int _currentIndex;

	int _numReads;
	int _lastMillis;

	int readSensor();
	int scaleSensorValue(int value);
	void setDefaultRanges();
};

#endif // BBSensor_h