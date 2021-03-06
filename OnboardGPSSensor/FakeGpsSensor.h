#ifndef FAKEGPSSENSOR
#define FAKEGPSSENSOR

#include "Arduino.h"
#include "SerialGpsSensor.h"

class FakeGpsSensor : public SerialGpsSensor
{
    public:
    //FakeGpsSensor() : SerialGpsSensor() {}
    FakeGpsSensor(Stream &input);
    ~FakeGpsSensor() {}
    
    //void Init( enGpsSerial comPort );
    void DoGpsSensor();
    
    private:
    float time;

};

#endif
