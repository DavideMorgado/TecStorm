//#include "DHT.h"

#define trigPin 48
#define echoPin 49
#define ventilator 50
#define buzzer 52
#define gasSensor A0
//#define DHTPIN 22     // what pin we're connected to
//#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define wire 47
#define valvula 46

#define GREEN 0
#define YELLOW 1
#define RED 2

//DHT dht(DHTPIN, DHTTYPE);

static int defaultDist;
static int defaultGas;

static int F;
static int B;
static int E;
static int V;

static int tempo=5;
static int yellowTime=0;

static int state = GREEN;
static int nextState = GREEN;

void setup() {
  // put your setup code here, to run once:Serial.begin(57600);
  Serial.begin(57600);
  while (!Serial);
  Serial.println("Serial Ready!");

  
  pinMode(gasSensor, INPUT);
  pinMode(wire, INPUT);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(ventilator, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(valvula, OUTPUT);
  defaultDist=readDistance();
  defaultGas=readGasSensor();
  //dht.begin();
}

void loop() {
  // put your main code here, to run repeatedly: 
  delay(500);
  if(readDistance()>defaultDist+5 || readDistance()<defaultDist-5) {
    F=0;
  }
  else F=1;

  if(readGasSensor()>defaultGas+5 || readGasSensor()<defaultGas-5) {
    if (F==0) {
      if(state==YELLOW) {
        if(millis()>=(yellowTime+(tempo*1000))) {
          nextState=RED;
        }
        else {
          nextState=YELLOW;
        }
      }
      else if(state==GREEN) {
        yellowTime=millis();
        nextState=YELLOW;
      }
      else nextState=RED;
    }
    else nextState=GREEN;
  }
  
  switch(state) {
    case(GREEN):
      setVentilator(LOW);
      setBuzzer(LOW);
      state=nextState;
      break;
    case(YELLOW):
      setVentilator(HIGH);
      setBuzzer(HIGH);
      state=nextState;
      break;
    case(RED):
      setVentilator(HIGH);
      setBuzzer(HIGH);
      turnValvula();
      state=nextState;
      break;
    default:
      state=RED;
      break;
  }
}

void setVentilator(int state) {
  if(state==HIGH) V=1;
  else V=0;
  digitalWrite(ventilator, state);
}

void setBuzzer(int state) {
  if(state==HIGH) B=1;
  else B=0;
  digitalWrite(buzzer, state);
}

int readGasSensor() {
  int tmp=analogRead(gasSensor);
  Serial.print("GAS: ");
  Serial.println(tmp);
  return tmp;
}

int readDistance() {
  long duration, distance;
  digitalWrite(trigPin, LOW);  // Added this line
  delayMicroseconds(2); // Added this line
  digitalWrite(trigPin, HIGH);
  //  delayMicroseconds(1000); - Removed this line
  delayMicroseconds(10); // Added this line
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;
  Serial.print("Distancia: ");
  Serial.println(distance);
  return distance;
}

int readWire() {
  return digitalRead(wire);
}

void turnValvula() {
  E=1;
  digitalWrite(valvula, HIGH);
  delay(50);
  digitalWrite(valvula, LOW);
}
/*float readHumidity() {
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  return dht.readHumidity();
}

float readTemp() {
  // Read temperature as Celsius
  return dht.readTemperature();
}*/


