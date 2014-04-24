#ifndef BBSensor_h
#define BBSensor_h

#include "ISubject.h"

// class BBSensor
class BBSensor : public ISubject
{
public:
	
	enum SensorType {
		ANALOG, 
		DIGITAL
	};

	// BBSensor();
	// BBSensor(SensorType);
	BBSensor(SensorType, int pin, bool invert=false);

	void begin();
	void setPin(int pin);
	void setInputRange(int low, int high);
	void setOutputRange(int low, int high);
	void setAveragingPeriod(int avgMillis);
	int  read();
	void update();
	bool isMotionDetected();

private:
	int  _pin;
	int  _sensorType;
	int  _inputRange[2];
	int  _outputRange[2];
	bool _invertOutput;
	// averaging
	int  _updateInterval;
	
	static const int DEFAULT_SMOOTHING = 10; // aka length of readings array
	static const int DEFAULT_UPDATE_INTERVAL = 50;
	int _smoothingFactor;
	int _readings[DEFAULT_SMOOTHING];
	unsigned long _runningTotal;
	int _rollingAverage;
	int _currentIndex;

	int _numReads;
	int _lastMillis;

	int readSensor();
	int scaleSensorValue(int value);
	void setDefaultRanges();
	void setSmoothingFactor(int=DEFAULT_SMOOTHING);
};

#endif // BBSensor_h