#ifndef SERIALGPSSENSOR

#define SERIALGPSSENSOR

#include "Arduino.h"
#include <GpsSensor.h>

class SerialGpsSensor : public GpsSensor
{
    public:
    SerialGpsSensor() : GpsSensor() {}
    ~SerialGpsSensor() {}
    
    void serialize( char ** res );
    
};

#endif
