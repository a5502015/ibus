#include <SPI.h>
#include <MFRC522.h>
#include <Ethernet.h>
#include <Wire.h> 
//----------------------------------
#define SS_PIN 53 //因為pin10乙太網路模組使用特別更改
#define RST_PIN 5
MFRC522 rfid(SS_PIN, RST_PIN);
EthernetClient client;
//--------------------------------
int as = 22;
int bs = 24;
int cs = 26;
int ds = 28;
int es = 30;
int fs = 32;
int gs = 34;
int hs = 36;
int is = 38;
//停靠站按鈕
byte mac[] = { 0xDE, 0xAD, 0x1E, 0xEF, 0xF4, 0x5D };
char server[] = "ibus.team-bob.org"; //改為定瑞的
//---------------------------------
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  Serial.println("hellow!");
  rfid.PCD_Init(); // Init MFRC522
  if(Ethernet.begin(mac)==0){
    Serial.println("link fail");
    }
  
  pinMode(as, INPUT);
  pinMode(bs, INPUT);
  pinMode(cs, INPUT);
  pinMode(ds, INPUT);
  pinMode(es, INPUT);
  pinMode(fs, INPUT);
  pinMode(gs, INPUT);
  pinMode(hs, INPUT);
  pinMode(is, INPUT);
  Serial.println("Start Bus Stop!");
}
//////////////////////////////////////
char Uuid[13] = "UID=";
char to_sn[10] = "to_sn=1";
char from_sn[10] = "from_sn=1";
char route[11] = "route=160&";
char sendtoserver[255];

char reg[5];
int puid[4];
/////////////////////////////////////////
void printHex(byte *buffer, byte bufferSize) {//rfid
  Uuid[4]='\0';
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
    
   
    puid[i] = buffer[i];
    sprintf(reg, "%x", puid[i]);
    strcat(Uuid, reg);
   
  }
  Serial.println();
  Serial.println(Uuid);
  Serial.println();
  Serial.println();
}
//------------------------------------------
void loop() {
  // put your main code here, to run repeatedly:
  int stopa = digitalRead(as);
  int stopb = digitalRead(bs);
  int stopc = digitalRead(cs);
  int stopd = digitalRead(ds);
  int stope = digitalRead(es);
  int stopf = digitalRead(fs);
  int stopg = digitalRead(gs);
  int stoph = digitalRead(hs);
  int stopi = digitalRead(is);
 // Serial.println("Start button.");
  
  if ((stopa + stopb + stopc + stopd + stope + stopf + stopg + stoph + stopi) == 0) {
    //Serial.println("Read RFID.");
    if ( ! rfid.PICC_IsNewCardPresent())  // Look for new cards
      return;
    if ( ! rfid.PICC_ReadCardSerial()) // Verify if the NUID has been readed
      return;
    Serial.println("The NUID tag is:");
    printHex(rfid.uid.uidByte, rfid.uid.size);

   // delay(500);
    rfid.PICC_HaltA();  // Halt PICC
    rfid.PCD_StopCrypto1();  // Stop encryption on PCD

    sendtoserver[0]='\0';
    strcat(sendtoserver, Uuid);
    strcat(sendtoserver, "&");
    strcat(sendtoserver, route);
    sendtoserver[23]='\0';
    strcat(sendtoserver, from_sn);
    strcat(sendtoserver, "&");
    sendtoserver[33]='\0';
    strcat(sendtoserver, to_sn);
    int i=0;
      while(sendtoserver[i]!='\0'){
           i++; 
        }
        Serial.print("lenght=");
        Serial.println(i);
    Serial.println(sendtoserver);
    //乙太網路
    
     if(client.connect(server, 3000)){
        Serial.println("good");

        client.println("POST /v2/reservation HTTP/1.1");
        client.println("Host: ibus.team-bob.org:3000");
       // client.println("User-Agent: iBus/1.0");
        client.println("Connection: close");
        client.println("Content-Type:application/x-www-form-urlencoded");
        client.println("Content-Length: 40");
        client.println("");           // 5/20 debug!!!
        client.println(sendtoserver);
       
        delay(500);
        }
        else{
          Serial.println("Please swipe the card again");
         
          }
    
  }
  else {
    
    //Serial.println("Read button.");
    if (stopa == 1 && (stopb + stopc + stopd + stope + stopf + stopg + stoph + stopi) == 0) {
      while (1) {
        stopa = digitalRead(as);
        if (stopa == 0) {
          break;
        }
      }
      //do some 1
      to_sn[0] = '\0';
      strcat(to_sn, "to_sn=1");
      Serial.println(to_sn);
    }
    //--------------------------------------------------------------
    if (stopb == 1 && (stopa + stopc + stopd + stope + stopf + stopg + stoph + stopi) == 0) {
      while (1) {
        stopb = digitalRead(bs);
        if (stopb == 0) {
          break;
        }
      }
      //do some 2
      to_sn[0] = '\0';
      strcat(to_sn, "to_sn=2");
      Serial.println(to_sn);
    }
    //------------------------------------------------------------
    if (stopc == 1 && (stopa + stopb + stopd + stope + stopf + stopg + stoph + stopi) == 0) {
      while (1) {
        stopc = digitalRead(cs);
        if (stopc == 0) {
          break;
        }
      }
      //do some 3
      to_sn[0] = '\0';
      strcat(to_sn, "to_sn=3");
      Serial.println(to_sn);
    }
    //------------------------------------------------
    if (stopd == 1 && (stopa + stopb + stopc + stope + stopf + stopg + stoph + stopi) == 0) {
      while (1) {
        stopd = digitalRead(ds);
        if (stopd == 0) {
          break;
        }
      }
      //do some 4
      to_sn[0] = '\0';
      strcat(to_sn, "to_sn=4");
      Serial.println(to_sn);
    }
    //-------------------------------------------------
    if (stope == 1 && (stopa + stopb + stopc + stopd + stopf + stopg + stoph + stopi) == 0) {
      while (1) {
        stope = digitalRead(es);
        if (stope == 0) {
          break;
        }
      }
      //do some 5
      to_sn[0] = '\0';
      strcat(to_sn, "to_sn=5");
      Serial.println(to_sn);
    }
    //--------------------------------------------
    if (stopf == 1 && (stopa + stopb + stopc + stopd + stope + stopg + stoph + stopi) == 0) {
      while (1) {
        stopf = digitalRead(fs);
        if (stopf == 0) {
          break;
        }
      }
      //do some 6
      to_sn[0] = '\0';
      strcat(to_sn, "to_sn=6");
      Serial.println(to_sn);
    }
    //--------------------------------------------------
    if (stopg == 1 && (stopa + stopb + stopc + stopd + stope + stopf + stoph + stopi) == 0) {
      while (1) {
        stopg = digitalRead(gs);
        if (stopg == 0) {
          break;
        }
      }
      //do some 7
      to_sn[0] = '\0';
      strcat(to_sn, "to_sn=7");
      Serial.println(to_sn);
    }
    //---------------------------------------------------
    if (stoph == 1 && (stopa + stopb + stopc + stopd + stope + stopf + stopg + stopi) == 0) {
      while (1) {
        stoph = digitalRead(hs);
        if (stoph == 0) {
          break;
        }
      }
      //do some 8
      to_sn[0] = '\0';
      strcat(to_sn, "to_sn=8");
      Serial.println(to_sn);
    }
    //----------------------------------------------
    if (stopi == 1 && (stopa + stopb + stopc + stopd + stope + stopf + stopg + stoph) == 0) {

      while (1) {
        stopi = digitalRead(is);
        if (stopi == 0) {
          break;
        }
      }
      //do some 9
      to_sn[0] = '\0';
      strcat(to_sn, "to_sn=9");
      Serial.println(to_sn);
    }
    //-----------------------------------------------
  }

}
