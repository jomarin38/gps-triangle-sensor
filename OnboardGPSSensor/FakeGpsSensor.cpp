#include "FakeGpsSensor.h"

void FakeGpsSensor::Init( enGpsSerial comPort )
{
	time=0;
	m_flat=45.0;
	m_flon=5.0;
	m_altme=0.0;
	m_age=0.0;
	m_valid=true;
}

void FakeGpsSensor::DoGpsSensor()
{
	m_flat = m_flat + time/1000.0 *2;
	m_flon = m_flon + time/1000.0;
	m_age = time;
	m_speedkm = sqrt(5.0);
	m_speedmi = 0.0;
	m_altme   = m_altme +time/1000.0 * 0.5 ;
	m_altft  = 0.0;
	m_coursedeg = 0.0;
	m_hdop  = 0.0;
	m_valid = true;
	m_sats = 0.0;
	time++;
}

