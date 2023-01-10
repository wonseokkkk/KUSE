#include <SPI.h>
#include <mcp_can.h>

//초음파 센서 코드
#define TRIG_PIN 5
#define ECHO_PIN 7

const int spiCSPin = 10;
int ledHIGH    = 1;
int ledLOW     = 0;

MCP_CAN CAN(spiCSPin);

void setup()
{
    Serial.begin(115200); 

    while (CAN_OK != CAN.begin(CAN_500KBPS,MCP_8MHz))
    {
        Serial.println("CAN BUS init Failed");
        delay(100);
    }
    Serial.println("CAN BUS Shield Init OK!");
    pinMode(TRIG_PIN,OUTPUT);
    pinMode(ECHO_PIN,INPUT);
 
}

void loop()
{   

  float cycletime;
  float distance;


  digitalWrite(TRIG_PIN, HIGH);
  delay(10);
  digitalWrite(TRIG_PIN,LOW);

  cycletime = pulseIn(ECHO_PIN,HIGH);
  distance = ((340 * cycletime)/10000)/2;
  
  unsigned char stmp[8] =  {0,0,0,0,0,0,0,0};
  
  if ( int(distance)<400){
    stmp[0] = 1;
    
  }
  else stmp[0] = 0;

  if(int(distance)>255){
    stmp[6] = int(distance) >> 8;
    stmp[7] = int(distance);
  }
  else {
    stmp[7] = int(distance);
  }

  Serial.print("Distance"); 
  Serial.print(int(distance));
  Serial.println("cm");

  CAN.sendMsgBuf(0x01, 0,  8 , stmp );

  delay(1000);

}