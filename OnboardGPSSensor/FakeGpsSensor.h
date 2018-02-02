#include "Arduino.h"

class FakeGpsSensor
{
    public:
    FakeGpsSensor() : m_flat( 0.0f), m_flon( 0.0f ), m_altme( 0 ), m_altft( 0 ), m_speedkm( 0 ), m_speedmi( 0 ), m_hdop( 0 ), m_age( 0 ), m_sats ( 0 ) {}
    ~FakeGpsSensor() {}
    
    enum enGpsSerial
    {
        SERIAL1 = 0x01,
        SERIAL2 = 0x02,
        SERIAL3 = 0x03,
    };
    
    void Init( enGpsSerial comPort );
    void DoGpsSensor();
    
    float GetLat()      { return m_flat; }
    float GetLon()      { return m_flon; }
    long  GetAltMe()    { return m_altme; }
    long  GetAltFt()    { return m_altft; }
    long  GetSpeedKm()  { return m_speedkm; }
    long  GetSpeedMi()  { return m_speedmi; }
    long  GetCourseDeg(){ return m_coursedeg; }
    long  GetHDOP()     { return (long)m_hdop; }
    long  GetAge()      { return (long)m_age; }
    bool  GetValid()    { return (long)m_valid; }
    long  GetSats()     { return m_sats; }
    
    // fence function
    void SetFencePoints( float Alat, float Alon, float Blat, float Blon ) { m_Alat = Alat; m_Alon = Alon, m_Blat = Blat; m_Blon = Blon; }
    long GetFenceDist( float Flat, float Flon ); // shortest distance to fence line in m
    
    protected:
    
    int      time;
    
    float    m_flat;
    float    m_flon;
    long     m_altme;
    long     m_altft;
    long     m_speedkm;
    long     m_speedmi;
    long     m_coursedeg;
    uint32_t m_hdop;
    uint32_t m_age;
    bool     m_valid;
    long     m_sats;
    
    // fence data
    float m_Alat;
    float m_Alon;
    float m_Blat;
    float m_Blon;
};
