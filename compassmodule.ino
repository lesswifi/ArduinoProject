#include <Wire.h>

#define Addr 0x1E               // 7-bit address of HMC5883 compass
int ledPin =  3; 
int mag;
void setup() {
  
  Serial.begin(9600);
  delay(100);                   // Power up delay
  Wire.begin();
  
  // Set operating mode to continuous
  Wire.beginTransmission(Addr); 
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
  pinMode(ledPin, OUTPUT); 
}

void loop() {
  int x, y, z;

  // Initiate communications with compass
  Wire.beginTransmission(Addr);
  Wire.write(byte(0x03));       // Send request to X MSB register
  Wire.endTransmission();

  Wire.requestFrom(Addr, 6);    // Request 6 bytes; 2 bytes per axis
  if(Wire.available() <=6) {    // If 6 bytes available
    x = Wire.read() << 8 | Wire.read();
    z = Wire.read() << 8 | Wire.read();
    y = Wire.read() << 8 | Wire.read();
  }
  
  // Print raw values
  Serial.print("X=");
  Serial.print(x);
  Serial.print(", Y=");
  Serial.print(y);
  Serial.print(", Z=");
  Serial.println(z);
  
  mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
  Serial.println(mag);
  if (mag>1000){
    digitalWrite(ledPin,HIGH);
  }
  if (digitalRead(ledPin) == HIGH){ 
    digitalWrite(ledPin,HIGH);
  }
}
