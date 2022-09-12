/*
  Based on Constantin Koch's Library
  added EVI config by Sandeep
*/

#include <RV-3028-C7.h>

RV3028 rtc;

//The below variables control what the date will be set to
int sec = 0;
int minute = 0;
int hour = 16;
int day = 4;
int date = 1;
int month = 8;
int year = 2019;

void setup() {

  Serial.begin(115200);
  while (!Serial);
  Serial.println("EVI interrupt Test manually code");

  Wire.begin();
  if (rtc.begin() == false) {
    Serial.println("Something went wrong, check wiring");
    while (1);
  }
  else
    Serial.println("RTC online!");
  delay(1000);

  //External event interrupt setup;
  rtc.clearBit(0x13, 0);  //TSS=0
  rtc.setBit(0x10, 7);    //TSE=1
  rtc.setBit(0x10, 2);    //EIE=1    //setting up registers according to datasheet
  rtc.clearBit(0x0E, 1);  //EVF=0 cleared flag
}

void loop()
{

  int a = rtc.readBit(0x0E, 1);    //read evi flag test
  Serial.print("EVI FLAG:");
  Serial.println(a);               //also alarm flag chcked manually and it working properly

  //PRINT TIME
  String currentTime = rtc.stringTimeStamp();
  Serial.println(currentTime + "Time");
  delay(1000);

}
