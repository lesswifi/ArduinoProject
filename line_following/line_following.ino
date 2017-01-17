#include <Servo.h>                           // Include servo library
#include <SoftwareSerial.h>
Servo servoRight;                            // Declare left servo
Servo servoLeft;
int qt1,qt2,qt3,qt4;
int k = 200;

void setup()                                 // Built in initialization block
{
  Serial.begin(9600);
  servoRight.attach(12);                     // Attach left signal to pin 12
  servoLeft.attach(13);
  
  servoRight.writeMicroseconds(1300);        
  servoLeft.writeMicroseconds(1700);
  delay(200);
  servoRight.writeMicroseconds(1500);        
  servoLeft.writeMicroseconds(1500);
  
  
}  
 
void loop()                                  // Main loop auto-repeats
{      
  qt1 = rcTime(6);
  qt2 = rcTime(7);
  qt3 = rcTime(8);
  qt4 = rcTime(9);
  //Serial.println(qt1);
  //Serial.println(qt2);
  //Serial.println(qt3);
  //Serial.println(qt4);
  //delay(2000);
  if(qt2>k && qt3>k){
    if(qt1>k || qt4>k){
      stop();
      delay(1000);
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
