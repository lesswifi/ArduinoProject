#include <Wire.h>
#include <SoftwareSerial.h>
#include <Servo.h>    
#define Rx 10
#define Tx 11
#define Addr 0x1E 
Servo servoRight;                            // Declare left servo
Servo servoLeft;
int qt1,qt2,qt3,qt4;
int k = 200;
SoftwareSerial Xbee(Rx,Tx);
int ledPin =  3; 
int mag;
int doneline=0;
int doneMag =0;
int ans=0;
int botA = 0;
int botB = 0;
int botC = 0;
int botD = 0;
int botE = 0;
int countA =0;
int countB =0;
int countC =0;
int countD =0;
int countE =0;
int sum=0;
int countsum=0;
const int LCDPin = 2;
char* myContinents[] = {"North America", "South America", "Asia", "Europe", "Australia", "Africa"};
SoftwareSerial mySerial = SoftwareSerial(255, LCDPin);
void setup() {
  //servo
  Serial.begin(9600);
  servoRight.attach(12);                     // Attach left signal to pin 12
  servoLeft.attach(13);
  servoRight.writeMicroseconds(1300);        
  servoLeft.writeMicroseconds(1700);
  delay(200);
  servoRight.writeMicroseconds(1500);        
  servoLeft.writeMicroseconds(1500);
  //communicate
  pinMode(4,INPUT);
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  Serial.begin(9600);
  Xbee.begin(9600);
  delay(500);
  //compass
  Serial.begin(9600);
  delay(100);                   // Power up delay
  Wire.begin();
  // Set operating mode to continuous
  Wire.beginTransmission(Addr); 
  Wire.write(byte(0x02));
  Wire.write(byte(0x00));
  Wire.endTransmission();
  pinMode(ledPin, OUTPUT); 
  //LCD
  mySerial.begin(9600);
  mySerial.write(12);
  pinMode(LCDPin,OUTPUT);

}

void loop() {
  digitalWrite(LCDPin, HIGH);
  randomSeed(analogRead(0));
  mySerial.write(12);
  mySerial.print(myContinents[random(0,5)]);
  
  //line following
  
  while(doneline ==0){
    qt1 = rcTime(6);
    qt2 = rcTime(7);
    qt3 = rcTime(8);
    qt4 = rcTime(9);
    if(qt2>k && qt3>k){
      if(qt1>k || qt4>k){
        stop();
        delay(500); 
        left();
        delay(1400);
        forward();
        delay(1000);  
        stop();
        doneline = 1;
      }
    }
    else if(qt1>k){
      right();
      delay(100);
    }
    else if(qt4>k){
      left();
      delay(100);
    }
    else if(qt2>k || qt3>k){
      forward();
      delay(100);
    }
  }
  servoRight.detach();
  servoLeft.detach();
  //compass
  while(doneMag<500){
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
    mag = sqrt(pow(x,2)+pow(y,2)+pow(z,2));
    //Serial.println(x);
    //Serial.println(y);
    //Serial.println(z);
    //Serial.println(mag);
    //delay(500);
    //mySerial.write(12);
    //mySerial.print(mag);
    if (mag>800){
      digitalWrite(ledPin,HIGH);
      ans=1;
    }
    
    doneMag++;
  }
  
   //communication
  if (ans==1){
    digitalWrite(LCDPin,HIGH);
    delay(100);
    mySerial.write(12);
    mySerial.print("Value is 1");
    Xbee.print('F');
    //delay(1000);
  }
  else if (ans==0){
    digitalWrite(LCDPin,HIGH);
    delay(100);
    mySerial.write(12);
    mySerial.print("Value is 0");
    Xbee.print('f');
    //delay(1000);
  }
  while(millis()<30000){
  if (Xbee.available()){
    char incoming = Xbee.read();
    //Serial.print(incoming);
    if(incoming == 'A' && countA==0){
      countA = 1;
      botA = 1;
    }
    if(incoming == 'B' && countB==0){
      countB = 1;
      botB = 1;
    }
    if(incoming == 'C' && countC==0){
      countC = 1;
      botC = 1;
    }
    if((incoming == 'D') && (countD==0)){
      countD = 1;
      botD = 1;
    }
    if(incoming == 'E' && countE==0){
      countE = 1;
      botE = 1;
    }
  }
  }
  sum = botA + botB + botC + botD + botE + ans; 
  digitalWrite(LCDPin,HIGH);
  delay(100);
  mySerial.write(12);
  mySerial.print(sum); 
  //delay(5000);
  while (true){
    if (Xbee.available()){
      char beeChar = Xbee.read();
      if (beeChar=='G'){
        dance();
      }
    }
  }
}


long rcTime(int pin){                               
  pinMode(pin, OUTPUT);         // Step 1, part 1
  digitalWrite(pin, HIGH);      // Step 1, part 2
  delay(1);                     // Step 2
  pinMode(pin, INPUT);          // Step 3  part 1
  digitalWrite(pin, LOW);       // Step 3, part 2
  long time  = micros();        // Step 4  
  while(digitalRead(pin));      // Step 5
  time = micros() - time;       // Step 6 & 7
  return time;                  
}  
void forward(){
  servoRight.writeMicroseconds(1300);        
  servoLeft.writeMicroseconds(1700);
}
void backward(){
  servoRight.writeMicroseconds(1700);        
  servoLeft.writeMicroseconds(1300);
}
void left(){
  servoRight.writeMicroseconds(1300);        
  servoLeft.writeMicroseconds(1300);
}
void right(){
  servoRight.writeMicroseconds(1700);        
  servoLeft.writeMicroseconds(1700);
}
void stop(){
  servoRight.writeMicroseconds(1500);        
  servoLeft.writeMicroseconds(1500);
}
void dance(){
  servoRight.attach(12);                     // Attach left signal to pin 12
  servoLeft.attach(13);
  right();
  delay(5000);
  servoRight.detach();
  servoLeft.detach();
  Xbee.print('H');
  servoRight.attach(12);                     // Attach left signal to pin 12
  servoLeft.attach(13);
  left();
  delay(5000);
  stop();
  servoRight.detach();
  servoLeft.detach();
  delay(1000000);
}

