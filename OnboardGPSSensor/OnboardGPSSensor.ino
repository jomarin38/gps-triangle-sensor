#define DEBUG_ENABLE
#define DATALINK_ENABLE
#define FAKE_GPS

#include <EEPROM.h>

#ifndef FAKE_GPS
#include "SerialGpsSensor.h"
#endif

#include "SDCardWriter.h"

#ifdef FAKE_GPS
#include "FakeGpsSensor.h"
#endif

#ifndef FAKE_GPS
SerialGpsSensor gps;
#endif

SDCardWriter writer;

#ifdef FAKE_GPS
FakeGpsSensor gps;
#endif

char serializedData[100];

int counter;

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + 3.
void EEPROMWritelong(int address, long value)
      {
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      byte four = (value & 0xFF);
      byte three = ((value >> 8) & 0xFF);
      byte two = ((value >> 16) & 0xFF);
      byte one = ((value >> 24) & 0xFF);

      //Write the 4 bytes into the eeprom memory.
      EEPROM.write(address, four);
      EEPROM.write(address + 1, three);
      EEPROM.write(address + 2, two);
      EEPROM.write(address + 3, one);
}
      
long EEPROMReadlong(long address)
      {
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF);
}

void setup()
{
	
#ifdef DEBUG_ENABLE
  Serial.begin(9600);
#endif
  while (!Serial) {
    ; 
  }

  long count = EEPROMReadlong(0);

  Serial.println(writer.init(count));
  
  EEPROMWritelong(0, count + 1);
  

#ifndef FAKE_GPS
  gps.Init( GpsSensor::SERIAL3 );
#endif



counter=0;

}

void loop()
{

  gps.DoGpsSensor();
  
  if (gps.isHomeSet() && writer.isReady()) {
	  Serial.println("Writing data to SD card ...");
	  if (writer.write(gps.serialize(serializedData))) {
		  Serial.println("Data successfully written");
	  }
	  else {
		  Serial.println("Failed to write data");
	  }
  }
  
  Serial.println(serializedData);

}


