#include <SPI.h>
#include <MFRC522.h>
#include<EEPROM.h>
#include<Wire.h>
#include "RTClib.h"


//#define SS_PIN 21 16
//#define RST_PIN 22 17
const int RST_PIN = 17;
const int SS_PIN = 16;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int count=0;
RTC_DS1307 rtc;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int relay=15;
void setup() {
  Serial.begin(115200);
  pinMode(2,OUTPUT);
  digitalWrite(relay,HIGH);
  pinMode(relay,OUTPUT);
 if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }
 rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  //rtc.adjust(DateTime(2019, 8, 23, 2, 32, 00));


  SPI.begin();      // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522
  Serial.println("take your card to the reader...");

  if (!EEPROM.begin(64000)) {
    Serial.println("Failed to initialise EEPROM");
    Serial.println("Restarting...");
    delay(1000);
    ESP.restart();
  }

}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    Serial.println(now.year(), DEC);
    Serial.println(EEPROM.readString(0));
    
  if (content.substring(1) == "03 6F CD 73") //change here the UID of the card/cards that you want to give access
  {
     digitalWrite(2,HIGH);
        
   // Serial.println("Authorized access");
    EEPROM.writeString(count,content.substring(1)) ;
    count = count + 11;
    Serial.print("\tRAJAN\t");
    EEPROM.writeString(count,+"\tRajan\t") ;
    count = count+7;
   
    
    DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    count= count + 2;
     Serial.print(now.day(), DEC);
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
     Serial.print(now.month(), DEC);
      String mon =  String((now.month())); 
     EEPROM.writeString(count,mon);
     count = count + 2;
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
   Serial.println(now.year(), DEC);
   String yr =  String((now.year())); 
   EEPROM.writeString(count,yr);
   count = count + 4;
   EEPROM.writeString(count,"\t");
   count = count + 1;
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    String weekday = (daysOfTheWeek[now.dayOfTheWeek()]);
     EEPROM.writeString(count, weekday);
//     EEPROM.writeString(count,"\t");
//     count = count + 1;
     Serial.print("time : ");
     
     Serial.print(now.hour(), DEC);
     String hr =  String((now.hour()));
     EEPROM.writeString(count,hr);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;
    Serial.print(now.minute(), DEC);
    String mint =  String((now.minute()));
     EEPROM.writeString(count,mint);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;

    String sec =  String(now.second());
        Serial.println(sec  );
     EEPROM.writeString(count,sec);
      count = count + 2;
      Serial.println("eeprom time...............................................................");
      
      Serial.println(count);
     
       Serial.println(EEPROM.readString(0));
       
    digitalWrite(relay,LOW);
    delay(1000);
     digitalWrite(relay,HIGH);
     Serial.println(" ");
    EEPROM.commit();
    digitalWrite(2,LOW);

  }
   else if (content.substring(1) == "EB 43 01 99") //change here the UID of the card/cards that you want to give access
  {
         digitalWrite(2,HIGH);
        
   // Serial.println("Authorized access");
    EEPROM.writeString(count,content.substring(1)) ;
    count = count + 11;
    Serial.print("\tTARUN\t");
    EEPROM.writeString(count,+"\tRajan\t") ;
    count = count+7;
   
    
    DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    count= count + 2;
     Serial.print(now.day(), DEC);
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
     Serial.print(now.month(), DEC);
      String mon =  String((now.month())); 
     EEPROM.writeString(count,mon);
     count = count + 2;
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
   Serial.println(now.year(), DEC);
   String yr =  String((now.year())); 
   EEPROM.writeString(count,yr);
   count = count + 4;
   EEPROM.writeString(count,"\t");
   count = count + 1;
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    String weekday = (daysOfTheWeek[now.dayOfTheWeek()]);
     EEPROM.writeString(count, weekday);
//     EEPROM.writeString(count,"\t");
//     count = count + 1;
     Serial.print("time : ");
     
     Serial.print(now.hour(), DEC);
     String hr =  String((now.hour()));
     EEPROM.writeString(count,hr);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;
    Serial.print(now.minute(), DEC);
    String mint =  String((now.minute()));
     EEPROM.writeString(count,mint);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;

    String sec =  String(now.second());
        Serial.println(sec  );
     EEPROM.writeString(count,sec);
      count = count + 2;
      Serial.println("eeprom time...............................................................");
      
      Serial.println(count);
     
       Serial.println(EEPROM.readString(0));
       
    digitalWrite(relay,LOW);
    delay(1000);
     digitalWrite(relay,HIGH);
     Serial.println(" ");
     EEPROM.commit();
     digitalWrite(2,LOW);
  }
   else if (content.substring(1) == "89 12 15 43") //change here the UID of the card/cards that you want to give access
  {
     digitalWrite(2,HIGH);
        
   // Serial.println("Authorized access");
    EEPROM.writeString(count,content.substring(1)) ;
    count = count + 11;
    Serial.print("\tRAJAN\t");
    EEPROM.writeString(count,+"\tRajan\t") ;
    count = count+7;
   
    
    DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    count= count + 2;
     Serial.print(now.day(), DEC);
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
     Serial.print(now.month(), DEC);
      String mon =  String((now.month())); 
     EEPROM.writeString(count,mon);
     count = count + 2;
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
   Serial.println(now.year(), DEC);
   String yr =  String((now.year())); 
   EEPROM.writeString(count,yr);
   count = count + 4;
   EEPROM.writeString(count,"\t");
   count = count + 1;
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    String weekday = (daysOfTheWeek[now.dayOfTheWeek()]);
     EEPROM.writeString(count, weekday);
//     EEPROM.writeString(count,"\t");
//     count = count + 1;
     Serial.print("time : ");
     
     Serial.print(now.hour(), DEC);
     String hr =  String((now.hour()));
     EEPROM.writeString(count,hr);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;
    Serial.print(now.minute(), DEC);
    String mint =  String((now.minute()));
     EEPROM.writeString(count,mint);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;

    String sec =  String(now.second());
        Serial.println(sec  );
     EEPROM.writeString(count,sec);
      count = count + 2;
      Serial.println("eeprom time...............................................................");
      
      Serial.println(count);
     
       Serial.println(EEPROM.readString(0));
       
    digitalWrite(relay,LOW);
    delay(1000);
     digitalWrite(relay,HIGH);
     Serial.println(" ");
    EEPROM.commit();
    digitalWrite(2,LOW);

  }

   else if (content.substring(1) == "42 4B D5 83") //change here the UID of the card/cards that you want to give access
  {
     digitalWrite(2,HIGH);
        
   // Serial.println("Authorized access");
    EEPROM.writeString(count,content.substring(1)) ;
    count = count + 11;
    Serial.print("\tRAJAN\t");
    EEPROM.writeString(count,+"\tRajan\t") ;
    count = count+7;
   
    
    DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    count= count + 2;
     Serial.print(now.day(), DEC);
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
     Serial.print(now.month(), DEC);
      String mon =  String((now.month())); 
     EEPROM.writeString(count,mon);
     count = count + 2;
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
   Serial.println(now.year(), DEC);
   String yr =  String((now.year())); 
   EEPROM.writeString(count,yr);
   count = count + 4;
   EEPROM.writeString(count,"\t");
   count = count + 1;
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    String weekday = (daysOfTheWeek[now.dayOfTheWeek()]);
     EEPROM.writeString(count, weekday);
//     EEPROM.writeString(count,"\t");
//     count = count + 1;
     Serial.print("time : ");
     
     Serial.print(now.hour(), DEC);
     String hr =  String((now.hour()));
     EEPROM.writeString(count,hr);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;
    Serial.print(now.minute(), DEC);
    String mint =  String((now.minute()));
     EEPROM.writeString(count,mint);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;

    String sec =  String(now.second());
        Serial.println(sec  );
     EEPROM.writeString(count,sec);
      count = count + 2;
      Serial.println("eeprom time...............................................................");
      
      Serial.println(count);
     
       Serial.println(EEPROM.readString(0));
       
    digitalWrite(relay,LOW);
    delay(1000);
     digitalWrite(relay,HIGH);
     Serial.println(" ");
    EEPROM.commit();
    digitalWrite(2,LOW);

  }

else if (content.substring(1) == "42 4B D5 83") //change here the UID of the card/cards that you want to give access
  {
     digitalWrite(2,HIGH);
        
   // Serial.println("Authorized access");
    EEPROM.writeString(count,content.substring(1)) ;
    count = count + 11;
    Serial.print("\tRAJAN\t");
    EEPROM.writeString(count,+"\tRajan\t") ;
    count = count+7;
   
    
    DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    count= count + 2;
     Serial.print(now.day(), DEC);
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
     Serial.print(now.month(), DEC);
      String mon =  String((now.month())); 
     EEPROM.writeString(count,mon);
     count = count + 2;
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
   Serial.println(now.year(), DEC);
   String yr =  String((now.year())); 
   EEPROM.writeString(count,yr);
   count = count + 4;
   EEPROM.writeString(count,"\t");
   count = count + 1;
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    String weekday = (daysOfTheWeek[now.dayOfTheWeek()]);
     EEPROM.writeString(count, weekday);
//     EEPROM.writeString(count,"\t");
//     count = count + 1;
     Serial.print("time : ");
     
     Serial.print(now.hour(), DEC);
     String hr =  String((now.hour()));
     EEPROM.writeString(count,hr);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;
    Serial.print(now.minute(), DEC);
    String mint =  String((now.minute()));
     EEPROM.writeString(count,mint);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;

    String sec =  String(now.second());
        Serial.println(sec  );
     EEPROM.writeString(count,sec);
      count = count + 2;
      Serial.println("eeprom time...............................................................");
      
      Serial.println(count);
     
       Serial.println(EEPROM.readString(0));
       
    digitalWrite(relay,LOW);
    delay(1000);
     digitalWrite(relay,HIGH);
     Serial.println(" ");
    EEPROM.commit();
    digitalWrite(2,LOW);

  }

else if (content.substring(1) == "A9 7A B8 3C") //change here the UID of the card/cards that you want to give access
  {
     digitalWrite(2,HIGH);
        
   // Serial.println("Authorized access");
    EEPROM.writeString(count,content.substring(1)) ;
    count = count + 11;
    Serial.print("\tRAJAN\t");
    EEPROM.writeString(count,+"\tRajan\t") ;
    count = count+7;
   
    
    DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    count= count + 2;
     Serial.print(now.day(), DEC);
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
     Serial.print(now.month(), DEC);
      String mon =  String((now.month())); 
     EEPROM.writeString(count,mon);
     count = count + 2;
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
   Serial.println(now.year(), DEC);
   String yr =  String((now.year())); 
   EEPROM.writeString(count,yr);
   count = count + 4;
   EEPROM.writeString(count,"\t");
   count = count + 1;
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    String weekday = (daysOfTheWeek[now.dayOfTheWeek()]);
     EEPROM.writeString(count, weekday);
//     EEPROM.writeString(count,"\t");
//     count = count + 1;
     Serial.print("time : ");
     
     Serial.print(now.hour(), DEC);
     String hr =  String((now.hour()));
     EEPROM.writeString(count,hr);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;
    Serial.print(now.minute(), DEC);
    String mint =  String((now.minute()));
     EEPROM.writeString(count,mint);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;

    String sec =  String(now.second());
        Serial.println(sec  );
     EEPROM.writeString(count,sec);
      count = count + 2;
      Serial.println("eeprom time...............................................................");
      
      Serial.println(count);
     
       Serial.println(EEPROM.readString(0));
       
    digitalWrite(relay,LOW);
    delay(1000);
     digitalWrite(relay,HIGH);
     Serial.println(" ");
    EEPROM.commit();
    digitalWrite(2,LOW);

  }
  
  
else if (content.substring(1) == "8A A7 AA 08") //change here the UID of the card/cards that you want to give access
  {
     digitalWrite(2,HIGH);
        
   // Serial.println("Authorized access");
    EEPROM.writeString(count,content.substring(1)) ;
    count = count + 11;
    Serial.print("\tRAJAN\t");
    EEPROM.writeString(count,+"\tRajan\t") ;
    count = count+7;
   
    
    DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    count= count + 2;
     Serial.print(now.day(), DEC);
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
     Serial.print(now.month(), DEC);
      String mon =  String((now.month())); 
     EEPROM.writeString(count,mon);
     count = count + 2;
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
   Serial.println(now.year(), DEC);
   String yr =  String((now.year())); 
   EEPROM.writeString(count,yr);
   count = count + 4;
   EEPROM.writeString(count,"\t");
   count = count + 1;
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    String weekday = (daysOfTheWeek[now.dayOfTheWeek()]);
     EEPROM.writeString(count, weekday);
//     EEPROM.writeString(count,"\t");
//     count = count + 1;
     Serial.print("time : ");
     
     Serial.print(now.hour(), DEC);
     String hr =  String((now.hour()));
     EEPROM.writeString(count,hr);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;
    Serial.print(now.minute(), DEC);
    String mint =  String((now.minute()));
     EEPROM.writeString(count,mint);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;

    String sec =  String(now.second());
        Serial.println(sec  );
     EEPROM.writeString(count,sec);
      count = count + 2;
      Serial.println("eeprom time...............................................................");
      
      Serial.println(count);
     
       Serial.println(EEPROM.readString(0));
       
    digitalWrite(relay,LOW);
    delay(1000);
     digitalWrite(relay,HIGH);
     Serial.println(" ");
    EEPROM.commit();
    digitalWrite(2,LOW);

  }

else if (content.substring(1) == "D7 A1 06 3D") //change here the UID of the card/cards that you want to give access
  {
     digitalWrite(2,HIGH);
        
   // Serial.println("Authorized access");
    EEPROM.writeString(count,content.substring(1)) ;
    count = count + 11;
    Serial.print("\tRAJAN\t");
    EEPROM.writeString(count,+"\tRajan\t") ;
    count = count+7;
   
    
    DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    count= count + 2;
     Serial.print(now.day(), DEC);
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
     Serial.print(now.month(), DEC);
      String mon =  String((now.month())); 
     EEPROM.writeString(count,mon);
     count = count + 2;
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
   Serial.println(now.year(), DEC);
   String yr =  String((now.year())); 
   EEPROM.writeString(count,yr);
   count = count + 4;
   EEPROM.writeString(count,"\t");
   count = count + 1;
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    String weekday = (daysOfTheWeek[now.dayOfTheWeek()]);
     EEPROM.writeString(count, weekday);
//     EEPROM.writeString(count,"\t");
//     count = count + 1;
     Serial.print("time : ");
     
     Serial.print(now.hour(), DEC);
     String hr =  String((now.hour()));
     EEPROM.writeString(count,hr);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;
    Serial.print(now.minute(), DEC);
    String mint =  String((now.minute()));
     EEPROM.writeString(count,mint);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;

    String sec =  String(now.second());
        Serial.println(sec  );
     EEPROM.writeString(count,sec);
      count = count + 2;
      Serial.println("eeprom time...............................................................");
      
      Serial.println(count);
     
       Serial.println(EEPROM.readString(0));
       
    digitalWrite(relay,LOW);
    delay(1000);
     digitalWrite(relay,HIGH);
     Serial.println(" ");
    EEPROM.commit();
    digitalWrite(2,LOW);

  }

  else if (content.substring(1) == "E7 E1 85 36") //change here the UID of the card/cards that you want to give access
  {
     digitalWrite(2,HIGH);
        
   // Serial.println("Authorized access");
    EEPROM.writeString(count,content.substring(1)) ;
    count = count + 11;
    Serial.print("\tRAJAN\t");
    EEPROM.writeString(count,+"\tRajan\t") ;
    count = count+7;
   
    
    DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    count= count + 2;
     Serial.print(now.day(), DEC);
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
     Serial.print(now.month(), DEC);
      String mon =  String((now.month())); 
     EEPROM.writeString(count,mon);
     count = count + 2;
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
   Serial.println(now.year(), DEC);
   String yr =  String((now.year())); 
   EEPROM.writeString(count,yr);
   count = count + 4;
   EEPROM.writeString(count,"\t");
   count = count + 1;
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    String weekday = (daysOfTheWeek[now.dayOfTheWeek()]);
     EEPROM.writeString(count, weekday);
//     EEPROM.writeString(count,"\t");
//     count = count + 1;
     Serial.print("time : ");
     
     Serial.print(now.hour(), DEC);
     String hr =  String((now.hour()));
     EEPROM.writeString(count,hr);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;
    Serial.print(now.minute(), DEC);
    String mint =  String((now.minute()));
     EEPROM.writeString(count,mint);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;

    String sec =  String(now.second());
        Serial.println(sec  );
     EEPROM.writeString(count,sec);
      count = count + 2;
      Serial.println("eeprom time...............................................................");
      
      Serial.println(count);
     
       Serial.println(EEPROM.readString(0));
       
    digitalWrite(relay,LOW);
    delay(1000);
     digitalWrite(relay,HIGH);
     Serial.println(" ");
    EEPROM.commit();
    digitalWrite(2,LOW);

  }

else if (content.substring(1) == "89 C7 D6 3B") //change here the UID of the card/cards that you want to give access
  {
     digitalWrite(2,HIGH);
        
   // Serial.println("Authorized access");
    EEPROM.writeString(count,content.substring(1)) ;
    count = count + 11;
    Serial.print("\tRAJAN\t");
    EEPROM.writeString(count,+"\tRajan\t") ;
    count = count+7;
   
    
    DateTime now = rtc.now();
     
     Serial.print("Date : ");
     String Day =  String((now.day())); 
    EEPROM.writeString(count,Day);
    count= count + 2;
     Serial.print(now.day(), DEC);
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
     Serial.print(now.month(), DEC);
      String mon =  String((now.month())); 
     EEPROM.writeString(count,mon);
     count = count + 2;
    Serial.print("/");
    EEPROM.writeString(count,"/");
    count = count + 1;
   Serial.println(now.year(), DEC);
   String yr =  String((now.year())); 
   EEPROM.writeString(count,yr);
   count = count + 4;
   EEPROM.writeString(count,"\t");
   count = count + 1;
     Serial.print("day:");
    Serial.println(daysOfTheWeek[now.dayOfTheWeek()]);
    String weekday = (daysOfTheWeek[now.dayOfTheWeek()]);
     EEPROM.writeString(count, weekday);
//     EEPROM.writeString(count,"\t");
//     count = count + 1;
     Serial.print("time : ");
     
     Serial.print(now.hour(), DEC);
     String hr =  String((now.hour()));
     EEPROM.writeString(count,hr);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;
    Serial.print(now.minute(), DEC);
    String mint =  String((now.minute()));
     EEPROM.writeString(count,mint);
      count = count + 2;
    Serial.print(':');
     EEPROM.writeString(count,":");
     count = count + 1;

    String sec =  String(now.second());
        Serial.println(sec  );
     EEPROM.writeString(count,sec);
      count = count + 2;
      Serial.println("eeprom time...............................................................");
      
      Serial.println(count);
     
       Serial.println(EEPROM.readString(0));
       
    digitalWrite(relay,LOW);
    delay(1000);
     digitalWrite(relay,HIGH);
     Serial.println(" ");
    EEPROM.commit();
    digitalWrite(2,LOW);

   }

 else   {
    digitalWrite(2,HIGH);
    delay(1000);
      digitalWrite(2,LOW); 
      delay(1000);
       digitalWrite(2,HIGH); 
       delay(1000); 
   Serial.println("you are not allowed");     
     digitalWrite(2,LOW);                  
    }
  
count=count+8;
delay(1000);


  
}
