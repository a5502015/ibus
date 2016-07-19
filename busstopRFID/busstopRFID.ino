/************************
 RFID
rst: pin 9
miso: pin 12
mosi: pin 11
sck: pin 13
sda pin 8
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
5/10
更改字串格式
試做乙太網路(未完成
******************************/
#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <Ethernet.h>
#include <LiquidCrystal_I2C.h>
#define SS_PIN 8 //因為pin10乙太網路模組使用特別更改
#define RST_PIN 9

LiquidCrystal_I2C lcd(0x27,16,2); 
MFRC522 rfid(SS_PIN, RST_PIN);

byte mac[] = { 0xDE, 0xAD, 0x1E, 0xEF, 0xF4, 0x5D };
char server[] = "ibus.team-bob.org"; //改為定瑞的
EthernetClient client;
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

char sendUid[13]="UID=";
char thisStop[10]="from_sn=1";
char arrStop[8]="to_sn=1";//6
char thisBus[10]="route=";
char reg[5];
int puid[4];
char sendtoserver[256];//16

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("hello");
  delay(500);
  SPI.begin(); // Init SPI bus
  Serial.println("hello");
  pinMode(busup,INPUT);
  pinMode(busdow,INPUT);
  pinMode(stopup,INPUT);
  pinMode(stopdow,INPUT);
  Serial.println("hello");
  lcd.init(); 
  lcd.backlight();
  Serial.println("hello");
  
  rfid.PCD_Init(); // Init MFRC522 
  /*
  if(Ethernet.begin(mac)==0){
      Serial.println("link fial");
     }
   */
  Serial.println("hello00");   
  Serial.println("NO.160 BUS_1  STOP");
  lcd.print("N"); lcd.print("O"); lcd.print(".");
  lcd.print("1"); lcd.print("6"); lcd.print("0"); lcd.print(" ");
  lcd.print("S"); lcd.print("T"); lcd.print("O"); lcd.print("P"); lcd.print(":");
  lcd.print("0"); lcd.print("0"); lcd.print("1");
  strcat(sendtoserver, "busNo=NO.160&arrStop=001&");
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
void successmesg(){
  lcd.setCursor(0,1);
  lcd.print("S");lcd.print("U");lcd.print("C");lcd.print("C");lcd.print("E");lcd.print("S");lcd.print("S");lcd.print("!");
  }
void errmesg(){
  lcd.setCursor(0,1);
  lcd.print("e");lcd.print("r");lcd.print("r");lcd.print("o");lcd.print("r");
  }
void clearlab(){
  lcd.setCursor(0,1);
  int i;
  for(i=0;i<16;i++){
    lcd.print(" ");
    }
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
       // sendtoserver[29]='\0';
        arrStop[0]='\0';
        strcat(arrStop,"to_sn=1");//41
        break;
      case 2:
        LCD002();
        //sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=2");//41
        break;
      case 3:
        LCD003();
        //sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=3");//41
        break;
      case 4:
        LCD004();
       // sendtoserver[29]='\0';
        arrStop[0]='\0';
        strcat(arrStop,"to_sn=4");//41
        break;
      case 5:
        LCD005();
        //sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=5");//41
        break;
      case 6:
        LCD006();
       // sendtoserver[29]='\0';
        arrStop[0]='\0';
        strcat(arrStop,"to_sn=6");//41
        break;
      case 7:
        LCD007();
       // sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=7");//41
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
       // sendtoserver[29]='\0';
        arrStop[0]='\0';
        strcat(arrStop,"to_sn=1");//41
        break;
      case 2:
        LCD002();
        //sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=2");//41
        break;
      case 3:
        LCD003();
        //sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=3");//41
        break;
      case 4:
        LCD004();
       // sendtoserver[29]='\0';
        arrStop[0]='\0';
        strcat(arrStop,"to_sn=4");//41
        break;
      case 5:
        LCD005();
        //sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=5");//41
        break;
      case 6:
        LCD006();
       // sendtoserver[29]='\0';
        arrStop[0]='\0';
        strcat(arrStop,"to_sn=6");//41
        break;
      case 7:
        LCD007();
       // sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=7");//41
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
       // sendtoserver[29]='\0';
        arrStop[0]='\0';
        strcat(arrStop,"to_sn=1");//41
        break;
      case 2:
        LCD002();
        //sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=2");//41
        break;
      case 3:
        LCD003();
        //sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=3");//41
        break;
      case 4:
        LCD004();
       // sendtoserver[29]='\0';
        arrStop[0]='\0';
        strcat(arrStop,"to_sn=4");//41
        break;
      case 5:
        LCD005();
        //sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=5");//41
        break;
      case 6:
        LCD006();
       // sendtoserver[29]='\0';
        arrStop[0]='\0';
        strcat(arrStop,"to_sn=6");//41
        break;
      case 7:
        LCD007();
       // sendtoserver[29]='\0';
         arrStop[0]='\0';
        strcat(arrStop,"to_sn=7");//41
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
  
    clearlab();
    
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
      
      sendtoserver[0]='\0';
      strcat(sendtoserver, sendUid);
      strcat(sendtoserver, "&");
      strcat(sendtoserver, thisBus);
      sendtoserver[23]='\0';
      strcat(sendtoserver, thisStop);
      strcat(sendtoserver, "&");
      sendtoserver[33]='\0';
      strcat(sendtoserver, arrStop);
      
      //int lenght=sendtoserver.lenght();
      Serial.println(sendtoserver);
      int i=0;
      while(sendtoserver[i]!='\0'){
           i++; 
        }
        Serial.print("lenght=");
        Serial.println(i);
        
      if(client.connect(server, 3000)){
        Serial.println("good");

        client.println("POST /v2/reservation HTTP/1.1");
        client.println("Host: ibus.team-bob.org:3000");
       // client.println("User-Agent: iBus/1.0");
        client.println("Connection: close");
        client.println("Content-Type:application/x-www-form-urlencoded");
        client.println("Content-Length: 40");
        client.println("");  
        client.println(sendtoserver);
        successmesg();
        delay(1000);
        }
        else{
          Serial.println("Please swipe the card again");
          errmesg();
          }
          /*
          if (client.available()) {
            char c = client.read();
            Serial.print(c);
           }
           */
      Serial.println(sendtoserver);
      
      sendUid[4]='\0';
      
      return;
      }
    else if(Bup==1||Bdw==1||Sup==1||Sdw==1||rfid.PICC_IsNewCardPresent()){
      
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
          //sendtoserver[16]='\0';
          thisBus[6]='\0';
          strcat(thisBus, "160&");//10
          //bus 0 sw
          linezero();
          break;
        case 1:
          Serial.print("NO.1 BUS");
          LCDNO(); LCD__1(); LCDstop(); 
          //sendtoserver[16]='\0';
          thisBus[6]='\0';
          strcat(thisBus, "001&");//8
          //bus 1 sw
          lineone();
          break;
        case 2:
          Serial.print("NO.2 BUS");
          LCDNO(); LCD__2(); LCDstop();
          //sendtoserver[16]='\0';
          thisBus[6]='\0';
          strcat(thisBus, "002&");//8
          //bus 2 sw
          linetwo();
          break;
        case 3:
          Serial.print("NO.3 BUS");
         // sendtoserver[16]='\0';
         // strcat(sendtoserver, "busNo=NO.  3&");//29
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
}
