/////////////////////////////////////////
// Code for Transmitter node 1 //
////////////////////////////////////////
// NRF24L01--------------ESP8266 NodeMCU
//    CE                      D4
//    CSN                     D8
//    SCK                     D5
//    MOSI                    D7
//    MISO                    D6
/////////////////////////////////////////
// Adapter NRF24L01------ESP8266 NodeMCU
//    VCC                     Vin
//    GND                     GND
/////////////////////////////////////////
//    MQ2-----------------ESP8266 NodeMCU
//    A0                      A0
//    GND                     GND
//    VCC                     V_in
//    LED connect             D0
//    LED warning             D1
//    Buzzer                  D2
//////////////////////////////////////////
#include <RF24.h>

#define CE_PIN D4
#define CS_PIN D8
RF24 radio(CE_PIN, CS_PIN);

float gasValue1;
const uint64_t pipe1 = 0x00000000000E;  // Địa chỉ ống truyền và nhận

#define Led_Connect D0
#define Led_Warning D1
#define Buzzer D2
void setup()
{
  pinMode(gasValue1, INPUT);
  pinMode(Led_Connect, OUTPUT);
  pinMode(Led_Warning, OUTPUT);
  pinMode(Buzzer, OUTPUT);  
  //Cai dat thong so ky thuat cho RF
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(pipe1);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();  
}
void loop()
{
  gasValue1 = analogRead(A0); 
  radio.write(&gasValue1, sizeof(gasValue1));
  Serial.print("Gas Value Node 1:");
  Serial.println(gasValue1);
  
  if (gasValue1 > 450) 
  {
    digitalWrite(Led_Connect, HIGH);
    digitalWrite(Buzzer, HIGH);

    digitalWrite(Led_Warning, HIGH);
    delay(100);
    digitalWrite(Led_Warning, LOW);
    delay(100);
  }
  else
  {
    digitalWrite(Led_Connect, HIGH);
    digitalWrite(Buzzer, LOW);
  }
}