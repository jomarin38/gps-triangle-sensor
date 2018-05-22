#define DEBUG_ENABLE
#define DATALINK_ENABLE
//#define FAKE_GPS

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

#define LED_PIN 6

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

void blink(long time, long pause, int repeat) {
	for (int i=0;i<repeat;i++) {
		digitalWrite(LED_PIN, HIGH);
		delay(time);
		digitalWrite(LED_PIN, LOW);
		delay(pause);
	}
}	

void setup()
{

  pinMode(LED_PIN, OUTPUT);
    	
  digitalWrite(LED_PIN, LOW);

  Serial.begin(9600);	
  while (!Serial) {
    ; 
  }

  long count = EEPROMReadlong(0);

  Serial.println(writer.init(count));
  
  if (writer.isReady()) {
	  blink(100,100,10);
	  EEPROMWritelong(0, count + 1);
  }

#ifndef FAKE_GPS
  gps.Init( GpsSensor::SERIAL3 );
#endif



counter=0;

}

void loop()
{

  gps.DoGpsSensor();
  gps.serialize(serializedData);
  
  if (gps.isHomeSet()) {
	if (writer.isReady()) {
		bool success = writer.write(serializedData);
#ifdef DEBUG_ENABLE
		if (success) {
			digitalWrite(LED_PIN, HIGH);
			Serial.print("Data successfully written : ");
		}
		else {
			blink(100,500,3);
			Serial.print("Failed to write data : ");
		}
#endif
	}
	else {
		blink(100,500,2);
	}
  }
  else {
	  blink(500,500,1);
  }
  
#ifdef DEBUG_ENABLE
  Serial.println(serializedData);
#endif

}


