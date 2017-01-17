#include <SoftwareSerial.h>

#define Rx 10
#define Tx 11

SoftwareSerial Xbee(Rx,Tx);

void setup() {

  // put your setup code here, to run once:
  pinMode(4,INPUT);
  pinMode(5,OUTPUT);
  digitalWrite(5,LOW);
  Serial.begin(9600);
  Xbee.begin(9600);
  delay(500);

}

void loop() {
// put your main code here, to run repeatedly:
//Serial.println(digitalRead(4));
  Xbee.print('s');   

  if (Xbee.available()){
    char incoming = Xbee.read();
    if (incoming=='s'){
      digitalWrite(5,HIGH);
      delay(1000);
      digitalWrite(5,LOW);
    }
    Serial.println(incoming);
  }
  delay(50);
}

