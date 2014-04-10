#ifndef BBSensor_h
#define BBSensor_h

class BBSensor
{
public:
	
	enum SensorType {
		ANALOG, 
		DIGITAL
	};
	BBSensor();
	BBSensor(SensorType);
	// BBSensor(int pin, SensorType sensorType);
	void setPin(int pin);
	void setInputRange(int low, int high);
	void setOutputRange(int low, int high);
	int read();
	bool isMotionDetected();

private:
	int _pin;
	int _sensorType;
	int _inputRange[2];
	int _outputRange[2];

	int readSensor();
	int scaleSensorValue(int value);
	void setDefaultRanges();
};

#endif // BBSensor_h