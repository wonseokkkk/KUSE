#include <SPI.h>
#include "mcp_can.h"

#define buzzer 7

const int spiCSPin = 10;
const int ledPin = 2;
boolean ledON = 1;

MCP_CAN CAN(spiCSPin);

void setup()
{
    Serial.begin(115200);
    pinMode(ledPin,OUTPUT);
    pinMode(buzzer, OUTPUT);
    while (CAN_OK != CAN.begin(CAN_500KBPS,MCP_8MHz))
    {
        Serial.println("CAN BUS Init Failed");
        delay(100);
    }
    Serial.println("CAN BUS  Init OK!");
}


void loop()
{
    unsigned char len = 0;
    unsigned char buf[8];

    if(CAN_MSGAVAIL == CAN.checkReceive())
    {
        CAN.readMsgBuf(&len, buf);
        

        
        unsigned long canId = CAN.getCanId();
				
        if(canId == 0x1){
          Serial.println();
          Serial.println("-----------------------------");
          Serial.print("Data from ID: 0x");
          Serial.println(canId, HEX);
          Serial.print("Distance = ");
          Serial.println(buf[6]  + buf[7]);

          if(buf[6]  + buf[7] < 5 ){
          tone(buzzer, 200);
          delay(100);
          }
          else {
            noTone(buzzer);
            delay(100);
          }
        }

        
        if(canId == 0x2){
          Serial.println();
          Serial.println("-----------------------------");
          Serial.print("Data from ID: 0x");
          Serial.println(canId, HEX);

        
          Serial.print(buf[4]);
          Serial.print(buf[5]);
          Serial.print(buf[6]);
          Serial.print(buf[7]);
          if(buf[4]==0 || buf[5]==0 || buf[6]==0 || buf[7]==0){
            tone(buzzer, 150);
            delay(100);
          }
          else {
            noTone(buzzer);
            delay(100);
          }          
        }
			
      
    }
}