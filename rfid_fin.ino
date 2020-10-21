#include "SPI.h"
#include "MFRC522.h"

#define SS_PIN 10
#define RST_PIN 9
#define SP_PIN 80

#define brown 7 //up
#define white 4 //down

MFRC522 rfid(SS_PIN, RST_PIN);

MFRC522::MIFARE_Key key;
void motorclose();
void motoropen();

void setup() {
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  Serial.begin(9600);
  SPI.begin();
  rfid.PCD_Init();
}

void loop() {
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

  // Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  // Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }

  String strID = "";
  for (byte i = 0; i < 4; i++) {
    strID +=
    (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(rfid.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  strID.toUpperCase();

 
  Serial.print("Tap card key: ");
  Serial.println(strID);
 // while(strID!=NULL){
   if(strID=="4A:BA:CA:73"){
    Serial.println("Verified");
    //motoropen();
    digitalWrite(brown, HIGH);             //opening
    digitalWrite(white,LOW);
    
    delay(5000);
    digitalWrite(brown,LOW);
    delay(8000);
     digitalWrite(brown, LOW);             //closing
    digitalWrite(white,HIGH);
    delay(4000);
    digitalWrite(white,LOW);
   // motorclose();
   
    }
  else
  Serial.println("WRONG ID!");
 // }
  


  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

/*void motoropen(){
  digitalWrite(8, HIGH);             //opening
    digitalWrite(7,LOW);
    delay(5000);
    digitalWrite(8,LOW);
}

void motorclose(){
  digitalWrite(8, LOW);             //opening
    digitalWrite(7,HIGH);
    delay(4000);
    digitalWrite(7,LOW);
   }*/
 
