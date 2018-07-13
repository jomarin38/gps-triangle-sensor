#include "UBXGpsSensor.h"

UBXGpsSensor::UBXGpsSensor(Stream &input) : serial(input)
{
	m_sats=0;
	
}

void UBXGpsSensor::init() 
{

}

void UBXGpsSensor::init(Stream &input) 
{
	serial=input;
}


void UBXGpsSensor::storeGPSData(NAV_PVT* pvt) 
{
	m_flat=pvt->lat/10000000.0f;
	m_flon=pvt->lon/10000000.0f;
	m_altme=pvt->height/1000;
	m_altft=m_altme;
	m_speedkm=pvt->gSpeed/1000.0f/1000.0f*3600.0f;
	m_speedmi=m_speedkm;
	m_coursedeg=pvt->heading;
	m_valid=((int)pvt->fixType)>1;
	//m_sats=1;
	m_sats=(int)pvt->numSV;
}

void UBXGpsSensor::DoGpsSensor()
{

}
