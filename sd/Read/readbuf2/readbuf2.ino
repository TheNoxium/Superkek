#include "SD.h"
const int chipSelect = D8;
void setup()
{
Serial.begin(9600);
Serial.print(“Initializing SD card&hellip;”);
pinMode(10, OUTPUT);
if (!SD.begin(chipSelect))
{
Serial.println(“Card failed, or not present”);
return;
}
Serial.println(“card initialized.”);
}

void loop()
{

}
