#ifndef SERIALGPSSENSOR
#define SERIALGPSSENSOR

#include "Arduino.h"
#include <GpsSensor.h>

class SerialGpsSensor : public GpsSensor
{
    public:
    SerialGpsSensor() : GpsSensor() {}
    ~SerialGpsSensor() {}
    
    char * serialize();
    
    private:
    char * floatToString(char * outstr, double val, byte precision, byte widthp);
    char lat[10];
    char lon[10];
    
};

#endif
