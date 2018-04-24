#include "SDCardWriter.h"

SDCardWriter::SDCardWriter()
{
	chipSelect=10;
	ready=false;
}

char * SDCardWriter::init(long count)
{
	if (!ready)
	{
	  pinMode(10, OUTPUT);     // 53 si ArduinoMega. Peu importe la valeur de chipSelect.
		
	  if (!SD.begin(chipSelect)) {
		ready=false;
		return "Card failed, or not present";
	  }
	  else {
		ready=true;
	  }
	}
    
    sprintf(fileName,"GPS%04ld.csv",count);
	
	char message[30];
	
	sprintf(message, "SD card ready : %s", fileName);
	
	return message;
	
}

bool SDCardWriter::write(char * data)
{
	if (ready) {
		File myFile = SD.open(fileName, FILE_WRITE);
		if (myFile) {
			myFile.println(data);
			myFile.close();
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
