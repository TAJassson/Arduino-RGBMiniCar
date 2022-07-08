
#include "BluetoothSerial.h"
//BTcontrollersupport
BluetoothSerial SerialBT;

#define resolution 8

const int freq_LED = 1000;
#define M1Pin1 4
#define M1Pin2 16
#define M2Pin1 19
#define M2Pin2 21
const int Channel_4_LED = 4; 
const int Channel_5_LED = 5; 
const int Channel_6_LED = 6;
const int TrigPin = 12;  //Port 1
const int EchoPin = 14;  //Port 2
int cm;
static const int PIN_LED_Red = 25;  
static const int PIN_LED_Green = 26;  
static const int PIN_LED_Blue = 27;      
byte brightness = 0;


void setup() {
 SerialBT.begin("Dammmmmmm"); //CreateBTConnecntion
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(M1Pin1,OUTPUT);
  pinMode(M1Pin2,OUTPUT);
  pinMode(M2Pin1,OUTPUT);
  pinMode(M2Pin2,OUTPUT);
  ledcSetup(Channel_4_LED, freq_LED, resolution);  
  ledcAttachPin(PIN_LED_Red, Channel_4_LED);       
  ledcSetup(Channel_5_LED, freq_LED, resolution);  
  ledcAttachPin(PIN_LED_Green, Channel_5_LED);       
  ledcSetup(Channel_6_LED, freq_LED, resolution); 
  ledcAttachPin(PIN_LED_Blue, Channel_6_LED); 
  pinMode(TrigPin, OUTPUT); 
  pinMode(EchoPin, INPUT); 
    Serial.begin(9600);
     
}

void loop() {
//超聲波Sensor
  digitalWrite(TrigPin, LOW); //低高低電平發一個短時間脈衝去TrigPin 
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58; //將回波時間換算成cm
  cm = (int(cm * 100)) / 100; //保留兩位小數 
  Serial.print(cm);
  Serial.print("cm");//串口輸出 
//超聲波Sensor
  Serial.println();
  delay(100); 
//getCMtocontrolRGBLight
     if (cm < 3 ) //if 10cm = warning and route to right 
     {
     Serial.print("To low");
     digitalWrite(M1Pin1, LOW);
     digitalWrite(M1Pin2, LOW);
     digitalWrite(M2Pin1, LOW);
     digitalWrite(M2Pin2, LOW);
       }
     if(cm >= 10)
     {
     ledcWrite(Channel_4_LED, 255);
     ledcWrite(Channel_5_LED, 255);
     ledcWrite(Channel_6_LED, 0); 
     }
     if(cm >=  20)
     {
     ledcWrite(Channel_4_LED, 0);
     ledcWrite(Channel_5_LED, 0);
     ledcWrite(Channel_6_LED, 255); 
     }        
//getCMtocontrolRGBLight
    if (SerialBT.available())
    {
    unsigned char rxdata = (unsigned char)SerialBT.read();
    Serial.write(rxdata);
//BT send data
//bind key 
    if (rxdata == '0') 
    {ledcWrite(Channel_4_LED, 0);
     ledcWrite(Channel_5_LED, 0);
     ledcWrite(Channel_6_LED, 0);
     delay(10000);
     }
    if (rxdata == 'R')  
    {ledcWrite(Channel_4_LED, 255);
     ledcWrite(Channel_5_LED, 0);
     ledcWrite(Channel_6_LED, 0); 
     delay (1000);      
     }
    if (rxdata == 'G')  
    {ledcWrite(Channel_4_LED, 0);
     ledcWrite(Channel_5_LED, 255);
     ledcWrite(Channel_6_LED, 0);  
     delay (1000);            
     }
     if (rxdata == 'B')  
    {ledcWrite(Channel_4_LED, 0);
     ledcWrite(Channel_5_LED, 0);
     ledcWrite(Channel_6_LED, 255);    
          delay (1000);         
     }
     if (rxdata == 'F')  
    {
      
      ledcWrite(Channel_4_LED, 0);
     ledcWrite(Channel_5_LED, 0);
     ledcWrite(Channel_6_LED, 0);  
     delay (80);
     ledcWrite(Channel_4_LED, 255);
     delay (1000);
     ledcWrite(Channel_4_LED, 0);
     ledcWrite(Channel_5_LED, 255);
     delay (1000);
     ledcWrite(Channel_4_LED, 0);
     ledcWrite(Channel_5_LED, 0); 
     ledcWrite(Channel_6_LED, 255);   
     delay (1000);
     ledcWrite(Channel_4_LED, 255);
     ledcWrite(Channel_5_LED, 0); 
     ledcWrite(Channel_6_LED, 255);   
     delay (1000);
     ledcWrite(Channel_4_LED, 255);
     ledcWrite(Channel_5_LED, 255); 
     ledcWrite(Channel_6_LED, 0);
     delay (1000);
     ledcWrite(Channel_4_LED, 0);
     ledcWrite(Channel_5_LED, 255); 
     ledcWrite(Channel_6_LED, 255); 
     delay (1000);  
     return;
     }
     if (rxdata == '4')  
    {digitalWrite(M1Pin1, 0);
     digitalWrite(M1Pin2, 255);
     digitalWrite(M2Pin1, 255 );
     digitalWrite(M2Pin2, 0);
     } 
     if (rxdata == '5')  //back
    {digitalWrite(M1Pin1, 255);
     digitalWrite(M1Pin2, LOW);
     digitalWrite(M2Pin1, LOW );
     digitalWrite(M2Pin2, 255);
     delay(150);
     digitalWrite(M1Pin1, LOW);
     digitalWrite(M1Pin2, LOW);
     digitalWrite(M2Pin1, LOW);
     digitalWrite(M2Pin2, LOW);
     delay(50);
     } 
     if (rxdata == '6')   //stop
    {digitalWrite(M1Pin1, LOW);
     digitalWrite(M1Pin2, LOW);
     digitalWrite(M2Pin1, LOW);
     digitalWrite(M2Pin2, LOW);
     delay(50); 
     } 
     if (rxdata == '8')  
    {digitalWrite(M1Pin1, 50);
     digitalWrite(M1Pin2, LOW);
     digitalWrite(M2Pin1, 50);
     digitalWrite(M2Pin2, LOW);
     delay(50);
     digitalWrite(M1Pin1, LOW);
     digitalWrite(M1Pin2, LOW);
     digitalWrite(M2Pin1, LOW);
     digitalWrite(M2Pin2, LOW);       
     }
     if (rxdata == '7')  
    {digitalWrite(M1Pin1, LOW);
     digitalWrite(M1Pin2, 50);
     digitalWrite(M2Pin1, LOW);
     digitalWrite(M2Pin2, 50);
     delay(50);
     digitalWrite(M1Pin1, LOW);
     digitalWrite(M1Pin2, LOW);
     digitalWrite(M2Pin1, LOW);
     digitalWrite(M2Pin2, LOW);     
     }  
  }
//bind key 
}
