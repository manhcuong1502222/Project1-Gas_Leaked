///////////////////////////
// Code for Transmitter node 1 //
/////////////////////////
// NRF24L01--------------Arduino UNO
//    VCC                     3.3V
//    GND                     GND
//    CE                      9
//    CSN                     10
//    SCK                     13
//    MOSI                    11
//    MISO                    12
//    MQ2-----------------Arduino UNO
//    A0                      A0
//    GND                     GND
//    VCC                     5V
//    LED connect             2
//    LED warning             3
//    Buzzer                  4
#include <RF24.h>
#include <SPI.h>
#include <nRF24L01.h>

#define CE_PIN 9
#define CS_PIN 10
RF24 radio(CE_PIN, CS_PIN);

float gasValue1;
const uint64_t pipe1 = 0xE8E8F0F0E1LL; //RF1

#define Led_Connect 2
#define Led_Warning 3
#define Buzzer 4
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