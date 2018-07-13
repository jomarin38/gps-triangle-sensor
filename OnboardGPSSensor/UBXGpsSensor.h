#ifndef UBXGPSSENSOR
#define UBXGPSSENSOR

#include "Arduino.h"

struct NAV_PVT {
  unsigned char cls;
  unsigned char id;
  unsigned short len;
  unsigned long iTOW;          // GPS time of week of the navigation epoch (ms)
  
  unsigned short year;         // Year (UTC) 
  unsigned char month;         // Month, range 1..12 (UTC)
  unsigned char day;           // Day of month, range 1..31 (UTC)
  unsigned char hour;          // Hour of day, range 0..23 (UTC)
  unsigned char minute;        // Minute of hour, range 0..59 (UTC)
  unsigned char second;        // Seconds of minute, range 0..60 (UTC)
  char valid;                  // Validity Flags (see graphic below)
  unsigned long tAcc;          // Time accuracy estimate (UTC) (ns)
  long nano;                   // Fraction of second, range -1e9 .. 1e9 (UTC) (ns)
  unsigned char fixType;       // GNSSfix Type, range 0..5
  char flags;                  // Fix Status Flags
  unsigned char reserved1;     // reserved
  unsigned char numSV;         // Number of satellites used in Nav Solution
  
  long lon;                    // Longitude (deg)
  long lat;                    // Latitude (deg)
  long height;                 // Height above Ellipsoid (mm)
  long hMSL;                   // Height above mean sea level (mm)
  unsigned long hAcc;          // Horizontal Accuracy Estimate (mm)
  unsigned long vAcc;          // Vertical Accuracy Estimate (mm)
  
  long velN;                   // NED north velocity (mm/s)
  long velE;                   // NED east velocity (mm/s)
  long velD;                   // NED down velocity (mm/s)
  long gSpeed;                 // Ground Speed (2-D) (mm/s)
  long heading;                // Heading of motion 2-D (deg)
  unsigned long sAcc;          // Speed Accuracy Estimate
  unsigned long headingAcc;    // Heading Accuracy Estimate
  unsigned short pDOP;         // Position dilution of precision
  short reserved2;             // Reserved
  unsigned long reserved3;     // Reserved
  unsigned char dummy[8];      // dummy not used
};

class UBXGpsSensor
{
	
    public:
    UBXGpsSensor(Stream &input);
    ~UBXGpsSensor() {}
    
    void DoGpsSensor();
    void storeGPSData(NAV_PVT* pvt);
    
    float GetLat() {return m_flat;}
    float GetLon() {return m_flon;}
    long GetAltMe() {return m_altme;}
    long GetSpeedKm() {return m_speedkm;}
    long GetSats() {return m_sats;}
    bool GetValid() {return m_valid;}
    void init();
    void init(Stream &input);
    
    
    private:
    
    Stream &serial;
    
    protected:
    float    m_flat;
    float    m_flon;
    long     m_altme;
    long     m_altft;
    long     m_speedkm;
    long     m_speedmi;
    long     m_coursedeg;
    bool     m_valid;
    long     m_sats;
     
};

#endif
