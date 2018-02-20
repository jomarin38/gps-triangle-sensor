#ifndef SERIALGPSSENSOR
#define SERIALGPSSENSOR

#include "Arduino.h"
#include <GpsSensor.h>

class SerialGpsSensor : public GpsSensor
{
    public:
    SerialGpsSensor();
    ~SerialGpsSensor() {}
    
    char * serialize(char * serializedData);
    void DoGpsSensor();
    
	unsigned long distToHome;
	
	
	boolean homeSet;
	boolean fix;
	long homeTime;
	
	float home_lat;
	float home_lon;
	float home_alt;
    
    private:
    char * floatToString(char * outstr, double val, byte precision, byte widthp);
    char lat[11];
    char lon[11];
    char home_lat_string[11];
    char home_lon_string[11];
    char alt[11];
    char speed[11];
    
};

#endif
