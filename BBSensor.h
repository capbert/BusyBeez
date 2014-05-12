#ifndef BBSensor_h
#define BBSensor_h

#include "ISubject.h"
#include <map>



struct SensorDescription;

class BBSensor : public ISubject
{
public:
	
	enum SensorType {
		EZ,
		PIR
	};


/*

	typedef std::multimap<SensorType, BBSensor *> SensorMap;
	typedef std::pair<SensorType, BBSensor *>SensorMapPair;
	typedef SensorMap::iterator SensorMapIterator;

	static SensorMap __sensors;

*/






	// BBSensor();
	// BBSensor(SensorType);
	BBSensor(int pin, SensorType);
	BBSensor(SensorType, int pin, bool invert=false);


	static BBSensor *create(SensorDescription);
	// static void updateAll();
	// static void attachType(SensorType, IObserver *);
	// static void detatchType(SensorType, IObserver *);
	static void syncRead(int pin, int ping); // micros, millis
	static void start(int);
	// static void beginConstantLoop(byte RX, byte TX, int ping);


	virtual void begin();
	// void begin();
	void setPin(int pin);
	int getPin();

	void invertOutput(bool);

	void setInputRange(int low, int high);
	void setOutputRange(int low, int high);
	// void setAveragingPeriod(int avgMillis);
	int  read();
	void update();
	// bool isMotionDetected();
	void configure(SensorDescription*);
private:
	int  _pin;
	
	int  _inputRange[2];
	int  _outputRange[2];
	bool _invertOutput;
	// averaging
	// int  _updateInterval;
	
	// static const int DEFAULT_SMOOTHING = 10; // aka length of readings array
	static const int DEFAULT_SMOOTHING = 5; // aka length of readings array
	// static const int DEFAULT_UPDATE_INTERVAL = 50;
	// int _smoothingFactor;
	int _readings[DEFAULT_SMOOTHING];
	// unsigned long _runningTotal;
	int _rollingAverage;
	byte _currentIndex;

	// int _numReads;
	// int _lastMillis;

	
	int scaleSensorValue(int value);
	// void setDefaultRanges();

	/* mode filter */



	// void iSort(int *, int);// insert sort algorithm



protected:
	int  _sensorType;
	virtual int readSensor();
	// void setSmoothingFactor(int=DEFAULT_SMOOTHING);
};


struct SensorRange {
	int low;
	int high;
};

struct SensorDescription {
	BBSensor::SensorType type;
	int pin;
	SensorRange inputRange;
	SensorRange outputRange;
};


#endif // BBSensor_h