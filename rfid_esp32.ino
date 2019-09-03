#include <SPI.h>
#include <MFRC522.h>
#include<EEPROM.h>

//#define SS_PIN 21 16
//#define RST_PIN 22 17
const int RST_PIN = 17;
const int SS_PIN = 16;
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
int count=0;
void setup() 
{
  pinMode(2,OUTPUT);
  Serial.begin(115200);   // Initiate a serial communication
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
void loop() 
{
  digitalWrite(2,HIGH);
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
  if (content.substring(1) == "03 6F CD 73") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access");
    EEPROM.writeString(count,+"A   time" ) ;
    Serial.println(EEPROM.readString(count));
    
  }
   else if (content.substring(1) == "EB 43 01 99") //change here the UID of the card/cards that you want to give access
  {
    Serial.println("Authorized access at 2");
     Serial.println("Authorized access");
    EEPROM.writeString(count,"B   time" );
    Serial.println(EEPROM.readString(count));
  }
 else   {
    Serial.println(" Access denied");
    Serial.println(" tryagain");                        
  
  }
  
  count=count+8;
  delay(1000);
  
} 
