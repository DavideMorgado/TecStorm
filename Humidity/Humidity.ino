#include "DHT.h"

#define DHTPIN 8// what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
int fan = 12;
int maxHum = 50;
int maxTemp = 30;

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  pinMode(fan, OUTPUT);
  //pinMode(DHTPIN,INPUT);
  Serial.begin(115200);  //57600 -- 9600 -- 115200 - 250000 -- 5000000 -- 1000000
  
  //SerialUSB.begin(115200); 
  Serial.println("Sensor test!");
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    //if( ((h==h)==0) || ((t==t)==0)){
    Serial.println("Failed to read from DHT sensor!");
    //return;
  }
  
  if(h > maxHum || t > maxTemp) {
      digitalWrite(fan, HIGH);
  } else {
     digitalWrite(fan, LOW); 
  }
  
  Serial.print("Humidity: "); 
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: "); 
  Serial.print(t);
  Serial.println(" *C ");
  
}
