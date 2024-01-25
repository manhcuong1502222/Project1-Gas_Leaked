//////////////////////////////////////
// Code for Gateway //
/////////////////////////////////////
// NRF24L01-----------ESP8266 NodeMCU
//    CE                    D4
//    CSN                   D8
//    SCK                   D5
//    MOSI                  D7
//    MISO                  D6
//////////////////////////////////////
//  Adapter NRF24L01---ESP8266 NodeMCU
//    VCC                   Vin
//    GND                   GND
//////////////////////////////////////
//    MQ2--------------ESP8266 NodeMCU
//    A0                    A0
//    GND                   GND
//    VCC                   3.3V
//////////////////////////////////////
// OLED I2C------------ESP8266 NodeMCU
//    VCC                   VCC
//    GND                   3.3V
//    SCL                   D1
//    SDA                   D2
//////////////////////////////////////
//    LED warning 1         D0
//    LED warning 2         D3
//////////////////////////////////////

#include <RF24.h>
#include <nRF24L01.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET -1
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define Led_Warning_N1 D3
#define Led_Warning_N2 D0
#define CE_PIN D4
#define CS_PIN D8
RF24 radio(CE_PIN, CS_PIN);
float gasValue1;
float gasValue2;
const uint64_t pipe1 = 0xE8E8F0F0E1LL; //RF1
const uint64_t pipe2 = 0x00000000000F;//RF2

void setup(){
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1,pipe1);
  radio.openReadingPipe(1,pipe2);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS);
  display.display();
  delay(1000);
  display.clearDisplay();

  pinMode(Led_Warning_N1, OUTPUT);
  pinMode(Led_Warning_N2, OUTPUT);
}
void loop(){
  RF1();
  RF2();
  OLED();
}
void OLED(){
  if ((gasValue1 > 450)&(gasValue2 > 450)){
    //Node 1
    digitalWrite(Led_Warning_N1, HIGH);
    delay(100);
    digitalWrite(Led_Warning_N1, LOW);
    delay(100);
    //Node 2
    digitalWrite(Led_Warning_N2, HIGH);
    delay(100);
    digitalWrite(Led_Warning_N2, LOW);
    delay(100);
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    //Node 1
    display.setCursor(0,0);
    display.println("Gas Value KV1:");
    display.setCursor(85,0);
    display.print(gasValue1);
    display.setCursor(15,30);
    display.println("Khu vuc 1 nguy hiem");
    //Node 2
    display.setCursor(0,15);
    display.println("Gas Value KV2:");  
    display.setCursor(85,15);
    display.print(gasValue2);
    display.setCursor(15,50);
    display.println("Khu vuc 2 nguy hiem");

    display.display();
 }
 if((gasValue1 > 450)&(gasValue2 < 450)){
    //Node 1
    digitalWrite(Led_Warning_N1, HIGH);
    delay(100);
    digitalWrite(Led_Warning_N1, LOW);
    delay(100);
    //Node 2
    digitalWrite(Led_Warning_N2, LOW);
    
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    //Node 1
    display.setCursor(0,0);
    display.println("Gas Value KV1:");
    display.setCursor(85,0);
    display.print(gasValue1);
    display.setCursor(15,30);
    display.println("Khu vuc 1 nguy hiem");
    //Node 2
    display.setCursor(0,15);
    display.println("Gas Value KV2:");  
    display.setCursor(85,15);
    display.print(gasValue2);
    display.setCursor(15,50);
    display.println("Khu vuc 2 an toan");
    
    display.display();
 }
 if((gasValue1 < 450)&(gasValue2 > 450)){
    //Node 1
    digitalWrite(Led_Warning_N1, LOW);
    //Node 2
    digitalWrite(Led_Warning_N2, HIGH);
    delay(100);
    digitalWrite(Led_Warning_N2, LOW);
    delay(100);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    //Node 1
    display.setCursor(0,0);
    display.println("Gas Value KV1:");
    display.setCursor(85,0);
    display.print(gasValue1);
    display.setCursor(15,30);
    display.println("Khu vuc 1 an toan");
    //Node 2
    display.setCursor(0,15);
    display.println("Gas Value KV2:");  
    display.setCursor(85,15);
    display.print(gasValue2);
    display.setCursor(15,50);
    display.println("Khu vuc 2 nguy hiem");
    
    display.display();
 }
 if((gasValue1 < 450)&(gasValue2 < 450)){
    //Node 1
    digitalWrite(Led_Warning_N1, LOW);
    //Node 2
    digitalWrite(Led_Warning_N2, LOW);

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    //Node 1
    display.setCursor(0,0);
    display.println("Gas Value KV1:");
    display.setCursor(85,0);
    display.print(gasValue1);
    display.setCursor(15,30);
    display.println("Khu vuc 1 an toan");
    //Node 2
    display.setCursor(0,15);
    display.println("Gas Value KV2:");  
    display.setCursor(85,15);
    display.print(gasValue2);
    display.setCursor(15,50);
    display.println("Khu vuc 2 an toan");
    
    display.display();
 }
}
void RF1(){
  radio.begin();
  radio.openReadingPipe(1,pipe1);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  delay(10);
  if (radio.available()){
    radio.read(&gasValue1, sizeof(gasValue1));
    Serial.print("Gas Value KV1:: ");
    Serial.println(gasValue1);
  }
  else{
    Serial.println("khong co tin hieu 1");
  }
}
void RF2(){
  radio.begin();
  radio.openReadingPipe(1,pipe2);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
  delay(10);
  if (radio.available()){
    radio.read(&gasValue2, sizeof(gasValue2));
    Serial.print("Gas Value KV2: ");
    Serial.println(gasValue2);
  }
  else{
    Serial.println("khong co tin hieu 2");
  }
}
