#include<Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup() {
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
 //rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2019, 8, 23, 2, 32, 00));
  
}

void loop() { 
  digitalWrite(2,HIGH);
  delay(3000);
   DateTime now = rtc.now();
    Serial.print("year:");
   Serial.println(now.year(), DEC);
    Serial.print("month:");
    Serial.println(now.month(), DEC);
    Serial.print("date:");
    Serial.println(now.day(), DEC);
    delay(2000);
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
     Serial.println("time");
     Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.println(now.second(), DEC);
    digitalWrite(2,HIGH);
    delay(5000);
}
