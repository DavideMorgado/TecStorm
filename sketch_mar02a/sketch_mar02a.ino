#include <SPI.h>
#include <Ethernet.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  while(!Serial);
  Serial.println("Serial Ready!");
  pinMode(52, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(52,HIGH);
  
}
