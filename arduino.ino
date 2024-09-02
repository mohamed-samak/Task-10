#include <Wire.h>

// C++ code
//
unsigned long previousMillis = 0; 
unsigned long currentMillis;      
float dt;
float yaw = 0.0;                 
int16_t GyroZ;  

void gyro_signals(){
  Wire.beginTransmission(0x68);
  Wire.write(0x1A);
  Wire.write(0x05);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x8);
  Wire.endTransmission();
  Wire.beginTransmission(0x68);
  Wire.write(0x43);
  Wire.endTransmission();
  Wire.requestFrom(0x68,6);
   GyroZ=Wire.read()<<8|Wire.read();}
  
  
void setup()
{
  Serial.begin(57600);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH);
  Wire.setClock(400000);
  Wire.begin();
  delay(250);
  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
}

void loop()
{
  gyro_signals();
  currentMillis = millis();
  dt = (currentMillis - previousMillis) / 1000.0; 
  previousMillis = currentMillis;
  yaw += ((float)GyroZ * dt) / 131.0; 

  Serial.print("Yaw: ");
  Serial.println(yaw);

  delay(100); 
}