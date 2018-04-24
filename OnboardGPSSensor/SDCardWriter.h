#ifndef SDCARDWRITER
#define SDCARDWRITER

#include "Arduino.h"

#include <SD.h>

class SDCardWriter
{
	private:
		int chipSelect;  //pin de l'Arduino reliee au CS du module SD
		bool ready;
		char fileName[12];
	
    public:
		SDCardWriter();
		~SDCardWriter() {}
		
		char * init(long count);
		
		bool write(char *data);
		
		void setShipSelect(int i) {chipSelect=i;}
		
		bool isReady() {return ready;}
    
};

#endif
