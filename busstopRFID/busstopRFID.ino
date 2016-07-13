#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);
int busup = 5;
int busdow = 4;
int stopup = 3;
int stopdow = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(busup,INPUT);
  pinMode(busdow,INPUT);
  pinMode(stopup,INPUT);
  pinMode(stopdow,INPUT);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
}
int busline = 0;
int busstopA;
int busstopB;
int busstopC;
int busstopD;
int busstopE;
int busstopF;
void printHex(byte *buffer, byte bufferSize) {//rfid
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
  Serial.println();
}
void linezero(){
  int Sup=digitalRead(stopup);
  int Sdw=digitalRead(stopdow);
  
  if(Sup==1&&Sdw==0){//up
    while(1){
      Sup=digitalRead(stopup);
      if(Sup==0)
        break;
      }
      if(busstopA<10){
        busstopA++;
        }
       else{
        busstopA=0;
        }
    }
    if(Sdw==1&&Sup==0){//down
      while(1){
        Sdw=digitalRead(stopdow);
        if(Sdw==0)
          break;
        }
        if(busstopA==0){
          busstopA=10;
          }
         else{
          busstopA--;
          }     
    } 
    Serial.print("_");
    Serial.print(busstopA);
    Serial.println("  STOP");
  //sw
}
void lineone(){
  int Sup=digitalRead(stopup);
  int Sdw=digitalRead(stopdow);
  
  if(Sup==1&&Sdw==0){//up
    while(1){
      Sup=digitalRead(stopup);
      if(Sup==0)
        break;
      }
     if(busstopB<10){
        busstopB++;
       }
      else{
        busstopB=0;
       }
    }
  if(Sdw==1&&Sup==0){//down
      while(1){
        Sdw=digitalRead(stopdow);
        if(Sdw==0)
          break;
        }
       if(busstopB==0){
          busstopB=10;
          }
         else{
          busstopB--;
          }
  }
    Serial.print("_");
    Serial.print(busstopB);
    Serial.println("  STOP");
  //sw
}
void linetwo(){
  int Sup=digitalRead(stopup);
  int Sdw=digitalRead(stopdow);
  
  if(Sup==1&&Sdw==0){//up
    while(1){
      Sup=digitalRead(stopup);
      if(Sup==0)
        break;
      }
      if(busstopC<10){
        busstopC++;
        }
       else{
        busstopC=0;
        }
    }
    if(Sdw==1&&Sup==0){//down
      while(1){
        Sdw=digitalRead(stopdow);
        if(Sdw==0)
          break;
       }
      if(busstopC==0){
          busstopC=10;
          }
         else{
          busstopC--;
         } 
    }
    Serial.print("_");
    Serial.print(busstopC);
    Serial.println("  STOP");
  //sw
}
void linethr(){
  int Sup=digitalRead(stopup);
  int Sdw=digitalRead(stopdow);
  
  if(Sup==1&&Sdw==0){
    while(1){
      Sup=digitalRead(stopup);
      if(Sup==0)
        break;
      }
      if(busstopD<10){
        busstopD++;
        }
       else{
        busstopD=0;
        }
    }
    if(Sdw==1&&Sup==0){//down
      while(1){
        Sdw=digitalRead(stopdow);
        if(Sdw==0)
          break;
       }
       if(busstopD==0){
          busstopD=10;
          }
         else{
          busstopD--;
          }
    }
    Serial.print("_");
    Serial.print(busstopD);
    Serial.println("  STOP");
  //sw
}
void linefou(){
  int Sup=digitalRead(stopup);
  int Sdw=digitalRead(stopdow);
  
  if(Sup==1&&Sdw==0){
    while(1){
      Sup=digitalRead(stopup);
      if(Sup==0)
        break;
      }
      if(busstopE<10){
        busstopE++;
        }
       else{
        busstopE=0;
        }
    }
    if(Sdw==1&&Sup==0){//down
      while(1){
        Sdw=digitalRead(stopdow);
        if(Sdw==0)
          break;
       }
       if(busstopE==0){
          busstopE=10;
          }
         else{
          busstopE--;
          }
    }
    Serial.print("_");
    Serial.print(busstopE);
    Serial.println("  STOP");
  //sw
}
void linefiv(){
  int Sup=digitalRead(stopup);
  int Sdw=digitalRead(stopdow);
  
  if(Sup==1&&Sdw==0){
    while(1){
      Sup=digitalRead(stopup);
      if(Sup==0)
        break;
      }
      if(busstopF<10){
        busstopF++;
        }
       else{
        busstopF=0;
        }
    }
    if(Sdw==1&&Sup==0){//down
      while(1){
        Sdw=digitalRead(stopdow);
        if(Sdw==0)
          break;
       }
       if(busstopF==0){
          busstopF=10;
          }
         else{
          busstopF--;
          }
    }
    Serial.print("_");
    Serial.print(busstopF);
    Serial.println("  STOP");
  //sw
}
  
void loop() {
  // put your main code here, to run repeatedly:
    int Bup=digitalRead(busup);
    int Bdw=digitalRead(busdow);
    

    if(Bup==1&&Bdw==0){//選擇路線 向上
      while(1){//防止彈跳
        Bup = digitalRead(busup);
        if(Bup==0)
          break;
        }
      if(busline<5){
        busline++;
        }
       else{
        busline=0;
        }
      }
    //--------------------------------------
    if(Bdw==1&&Bup==0){
      while(1){
        Bdw = digitalRead(busdow);
        if(Bdw==0)
          break;
        }
      if(busline==0){
        busline=5;
        }
       else{
        busline--;
        }
      }
      switch(busline){
        case 0:
          Serial.print("NO.0 BUS");
          //bus 0 sw
          linezero();
          break;
        case 1:
          Serial.print("NO.1 BUS");
          //bus 1 sw
          lineone();
          break;
        case 2:
          Serial.print("NO.2 BUS");
          //bus 2 sw
          linetwo();
          break;
        case 3:
          Serial.print("NO.3 BUS");
          //bus 3 sw
          linethr();
          break;
        case 4:
          Serial.print("NO.4 BUS");
          //bus 4 sw
          linefou();
          break;
        case 5:
          Serial.print("NO.5 BUS");
          //bus 5 sw
          linefiv();
          break;
        }
        delay(50);

   if ( ! rfid.PICC_IsNewCardPresent()) { // Look for new cards
      Serial.println(rfid.PICC_IsNewCardPresent());
      return;
      
      }
   if ( ! rfid.PICC_ReadCardSerial()) // Verify if the NUID has been readed
      return;

   Serial.println(rfid.PICC_IsNewCardPresent());
   Serial.println("The NUID tag is:");
   printHex(rfid.uid.uidByte, rfid.uid.size);
   delay(5000);
   rfid.PICC_HaltA();  // Halt PICC
   rfid.PCD_StopCrypto1();  // Stop encryption on PCD
}
