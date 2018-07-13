#include "SerialGpsSensor.h"

SerialGpsSensor::SerialGpsSensor(Stream &input) : UBXGpsSensor(input) 
{
	homeSet = false;
	homeTime = 0;
	home_alt = 0;
	distToHome = 0;
	fix = false;
}

char * SerialGpsSensor::serialize(char * serializedData)
{
	if (fix) {
	
		if (homeSet) {
			
			
			long time = (millis()-homeTime)/10;
			floatToString(lat,GetLat(),5,10);
			
			sprintf(serializedData, 
					"%10ld,%s,%s,%s,%s,%s,%s",
					time,
					lat,
					floatToString(lon,GetLon(),5,10),
					floatToString(home_lat_string,home_lat,5,10),
					floatToString(home_lon_string,home_lon,5,10),
					floatToString(speed,GetSpeedKm(),5,10),
					floatToString(alt,GetAltMe(),5,10));
		}
		else {
			sprintf(serializedData, "h%1d Home not set", GetSats());
		}
	}
	else {
		sprintf(serializedData, "f%1d GPS not fixed", GetSats());
	}
	return serializedData;
	
}

void SerialGpsSensor::DoGpsSensor()
{
	UBXGpsSensor::DoGpsSensor();
    
    if (!fix) {
		if (GetValid()) {
			fix = true;
			if (!homeSet) {
				homeTime = (millis() + 5000);
			}
		} else {
		fix = false;
		}
	}
    
    if (!homeSet && homeTime > 0 && (homeTime < millis())) {
      homeSet = true;
      home_lat = GetLat();
      home_lon = GetLon();
      home_alt = GetAltMe();
    }

}

char * SerialGpsSensor::floatToString(char * outstr, double val, byte precision, byte widthp){
 char temp[16]; //increase this if you need more digits than 15
 byte i;

 temp[0]='\0';
 outstr[0]='\0';

 if(val < 0.0){
   strcpy(outstr,"-\0");  //print "-" sign
   val *= -1;
 }

 if( precision == 0) {
   strcat(outstr, ltoa(round(val),temp,10));  //prints the int part
 }
 else {
   unsigned long frac, mult = 1;
   byte padding = precision-1;
   
   while (precision--)
     mult *= 10;

   val += 0.5/(float)mult;      // compute rounding factor
   
   strcat(outstr, ltoa(floor(val),temp,10));  //prints the integer part without rounding
   strcat(outstr, ".\0"); // print the decimal point

   frac = (val - floor(val)) * mult;

   unsigned long frac1 = frac;

   while(frac1 /= 10)
     padding--;

   while(padding--)
     strcat(outstr,"0\0");    // print padding zeros

   strcat(outstr,ltoa(frac,temp,10));  // print fraction part
 }

 // generate width space padding
 if ((widthp != 0)&&(widthp >= strlen(outstr))){
   byte J=0;
   J = widthp - strlen(outstr);

   for (i=0; i< J; i++) {
     temp[i] = ' ';
   }

   temp[i++] = '\0';
   strcat(temp,outstr);
   strcpy(outstr,temp);
 }

 return outstr;
}
