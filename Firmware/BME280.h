// BME280.h

#ifndef _BME280_h
#define _BME280_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class BME280Class
{
 protected:


 public:
	void init();
};

extern BME280Class BME280;

#endif

