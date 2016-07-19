/************************
 RFID
rst: pin 9
miso: pin 12
mosi: pin 11
sck: pin 13
sda pin 10
//////////////
BUS line 
up pin 5
down pin 4
//////////////////
stop
up pin 3
down pin2
2016/5/1
新增LCD螢幕功能
******************************/
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

#define SS_PIN 10
#define RST_PIN 9
MFRC522 rfid(SS_PIN, RST_PIN);
int busup = 5;
int busdow = 4;
int stopup = 3;
int stopdow = 2;
//----------------------------
int busline = 0;
int busstopA = 1;
int busstopB = 1;
int busstopC = 1;
int busstopD = 1;
int busstopE = 1;
int busstopF = 1;

char sendUid[13]="UID:";
char reg[5];
int puid[4];
char sendtoserver[256]="FCU001,";//7

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(busup,INPUT);
  pinMode(busdow,INPUT);
  pinMode(stopup,INPUT);
  pinMode(stopdow,INPUT);
  
  lcd.init(); 
  lcd.backlight();
  
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
  
  Serial.println("NO.160 BUS_1  STOP");
  lcd.print("N"); lcd.print("O"); lcd.print(".");
  lcd.print("1"); lcd.print("6"); lcd.print("0"); lcd.print(" ");
  lcd.print("S"); lcd.print("T"); lcd.print("O"); lcd.print("P"); lcd.print(":");
  lcd.print("0"); lcd.print("0"); lcd.print("1");
  strcat(sendtoserver, "NO,160,STOP:001,");
}

void printHex(byte *buffer, byte bufferSize) {//rfid
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);

    puid[i]=buffer[i];
    sprintf(reg,"%x",puid[i]);
    strcat(sendUid,reg);
 
  }
  Serial.println();
  Serial.println();
}
//---------------LCD列印---------------------
void LCDNO(){
  lcd.setCursor(0, 0);
  lcd.print("N"); lcd.print("O"); lcd.print(".");
  
  }
void LCD160(){
  lcd.setCursor(3, 0);
  lcd.print("1"); lcd.print("6");  lcd.print("0");
  }
void LCDstop(){
  lcd.setCursor(7, 0);
  lcd.print("S"); lcd.print("T"); lcd.print("O"); lcd.print("P"); lcd.print(":");
  }
void LCD001(){
  lcd.setCursor(12, 0);
  lcd.print("0"); lcd.print("0"); lcd.print("1");
  }
void LCD002(){
  lcd.setCursor(12, 0);
  lcd.print("0"); lcd.print("0"); lcd.print("2");
  }
void LCD003(){
  lcd.setCursor(12, 0);
  lcd.print("0"); lcd.print("0"); lcd.print("3");
  }
void LCD004(){
  lcd.setCursor(12, 0);
  lcd.print("0"); lcd.print("0"); lcd.print("4");

  }
void LCD005(){
  lcd.setCursor(12, 0);
  lcd.print("0"); lcd.print("0"); lcd.print("5");
  }
void LCD006(){
  lcd.setCursor(12, 0);
  lcd.print("0"); lcd.print("0"); lcd.print("6");
  }
void LCD007(){
  lcd.setCursor(12, 0);
  lcd.print("0"); lcd.print("0"); lcd.print("7");
  }
void LCD__1(){
  lcd.setCursor(3, 0);
  lcd.print(" "); lcd.print(" ");  lcd.print("1");
  }
void LCD__2(){
  lcd.setCursor(3, 0);
  lcd.print(" "); lcd.print(" ");  lcd.print("2");
  }
//----------車站----------------
void linezero(){//160LINE
  int Sup=digitalRead(stopup);
  int Sdw=digitalRead(stopdow);
  
  if(Sup==1&&Sdw==0){//up
    while(1){
      Sup=digitalRead(stopup);
      if(Sup==0)
        break;
      }
      if(busstopA<7){
        busstopA++;
        }
       else{
        busstopA=1;
        }
    }
    if(Sdw==1&&Sup==0){//down
      while(1){
        Sdw=digitalRead(stopdow);
        if(Sdw==0)
          break;
        }
        if(busstopA==1){
          busstopA=7;
          }
         else{
          busstopA--;
          }     
    } 
    Serial.print("_");
    Serial.print(busstopA);
    Serial.println("  STOP");
    
  //sw
    switch(busstopA){
      case 1:
        LCD001();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:001,");//23
        break;
      case 2:
        LCD002();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:002,");//23
        break;
      case 3:
        LCD003();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:003,");//23
        break;
      case 4:
        LCD004();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:004,");//23
        break;
      case 5:
        LCD005();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:005,");//23
        break;
      case 6:
        LCD006();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:006,");//23
        break;
      case 7:
        LCD007();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:007,");//23
        break;
      }
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
     if(busstopB<7){
        busstopB++;
       }
      else{
        busstopB=1;
       }
    }
  if(Sdw==1&&Sup==0){//down
      while(1){
        Sdw=digitalRead(stopdow);
        if(Sdw==0)
          break;
        }
       if(busstopB==0){
          busstopB=7;
          }
         else{
          busstopB--;
       }
     
  }
    Serial.print("_");
    Serial.print(busstopB);
    Serial.println("  STOP");
  //sw
  
  switch(busstopB){
      case 1:
        LCD001();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:001,");//23
        break;
      case 2:
        LCD002();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:002,");//23
        break;
      case 3:
        LCD003();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:003,");//23
        break;
      case 4:
        LCD004();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:004,");//23
        break;
      case 5:
        LCD005();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:005,");//23
        break;
      case 6:
        LCD006();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:006,");//23
        break;
      case 7:
        LCD007();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:007,");//23
        break;
      }
      
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
      if(busstopC<7){
        busstopC++;
        }
       else{
        busstopC=1;
        }
    }
    if(Sdw==1&&Sup==0){//down
      while(1){
        Sdw=digitalRead(stopdow);
        if(Sdw==0)
          break;
       }
      if(busstopC==0){
          busstopC=7;
          }
         else{
          busstopC--;
         } 
    }
    Serial.print("_");
    Serial.print(busstopC);
    Serial.println("  STOP");
  //sw
  
  switch(busstopC){
      case 1:
        LCD001();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:001,");//23
        break;
      case 2:
        LCD002();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:002,");//23
        break;
      case 3:
        LCD003();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:003,");//23
        break;
      case 4:
        LCD004();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:004,");//23
        break;
      case 5:
        LCD005();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:005,");//23
        break;
      case 6:
        LCD006();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:006,");//23
        break;
      case 7:
        LCD007();
        sendtoserver[14]='\0';
        strcat(sendtoserver,"STOP:007,");//23
        break;
      }
      
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
    int Sup=digitalRead(stopup);
    int Sdw=digitalRead(stopdow);
  
   
    
    if(Bup==0&&Bdw==0&&Sup==0&&Sdw==0) {
      if ( ! rfid.PICC_IsNewCardPresent())  // Look for new cards
           return;
      if ( ! rfid.PICC_ReadCardSerial()) // Verify if the NUID has been readed
           return;
      Serial.println("The NUID tag is:");
      printHex(rfid.uid.uidByte, rfid.uid.size);
     
      delay(500);
      rfid.PICC_HaltA();  // Halt PICC
      rfid.PCD_StopCrypto1();  // Stop encryption on PCD
      
      sendtoserver[23]='\0';
      strcat(sendtoserver, sendUid);
      Serial.println(sendtoserver);
      sendUid[4]='\0';
      
      return;
      }
    else if(Bup==1||Bdw==1||Sup==1||Sdw==1||rfid.PICC_IsNewCardPresent()){
       // sendtoserver[7]='\0';
        //sendUid[4]='\0';
        if(Bup==1&&Bdw==0){//選擇路線 向上
      while(1){//防止彈跳
        Bup = digitalRead(busup);
        if(Bup==0)
          break;
        }
      if(busline<2){
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
        busline=2;
        }
       else{
        busline--;
        }
      }
     // sendtoserver[7]='\0';
      switch(busline){
        case 0:
          Serial.print("NO.160 BUS");
          LCDNO(); LCD160(); LCDstop(); 
          sendtoserver[7]='\0';
          strcat(sendtoserver, "NO.160,");//14
          //bus 0 sw
          linezero();
          break;
        case 1:
          Serial.print("NO.1 BUS");
          LCDNO(); LCD__1(); LCDstop(); 
          sendtoserver[7]='\0';
          strcat(sendtoserver, "NO.  1,");//14
          //bus 1 sw
          lineone();
          break;
        case 2:
          Serial.print("NO.2 BUS");
          LCDNO(); LCD__2(); LCDstop();
          sendtoserver[7]='\0';
          strcat(sendtoserver, "NO.  2,");//14
          //bus 2 sw
          linetwo();
          break;
        case 3:
          Serial.print("NO.3 BUS");
         // sendtoserver[7]='\0';
         // strcat(sendtoserver, "NO.  3,");//14
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
      }
     // sendtoserver[7]='\0';
      //sendUid[4]='\0';
      
}
