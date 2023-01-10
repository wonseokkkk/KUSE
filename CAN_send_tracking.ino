#include <SPI.h>
#include <mcp_can.h>

#define X1 4 //Left2
#define X2 5 //Left1
#define X3 6 //Right1
#define X4 7 //Right2

const int spiCSPin = 10;
int ledHIGH    = 1;
int ledLOW     = 0;

int Left1 = X2;
int Left2 = X1;
int Right1 = X3;
int Right2 = X4;

int val_L1, val_L2, val_R1, val_R2;

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

    pinMode(Left1, INPUT);
    pinMode(Left2, INPUT);
    pinMode(Right1, INPUT);
    pinMode(Right2, INPUT);  
}


unsigned char stmp[8] = {0,0,0,0,0,0,0,0};
    
void loop()
{   

  val_L1 = digitalRead(Left1);
  val_L2 = digitalRead(Left2);
  val_R1 = digitalRead(Right1);
  val_R2 = digitalRead(Right2);
  Serial.println();
  stmp[4] = val_L1;
  stmp[5] = val_L2;
  stmp[6] = val_R1;
  stmp[7] = val_R2;

  Serial.print(stmp[4]);
  Serial.print(stmp[5]);
  Serial.print(stmp[6]);
  Serial.print(stmp[7]);

  CAN.sendMsgBuf(0x02, 0, 8, stmp);
  delay(1000);
}