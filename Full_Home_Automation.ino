//Header Files
#include <dht.h>
//#include<SoftwareSerial.h>

//Bluetooth
//SoftwareSerial bltmain(12,13);
//int btmain;

//Relay pins
int light1 = 2;
int light2 = 3;
int fan1 = 4;
int light3 = 5;
int light4 = 6;
int fan2 = 7;
int waterPump1 = 8;
int waterPump2 = 11;

//Sonar pins
#define trig1 9
#define echo1 10
#define trig2 12
#define echo2 13
float duration, distance, sonar1, sonar2;

//Water L.S-1
const int read1 = A0;
int Value1;
int MWL1;

//Water L.S-2
const int read2 = A1;
int Value2;
int MWL2;

//dht sensor(qty=2)
#define datp1 A2 // Defines pin number to which the sensor is connected
#define datp2 A3
dht DHT1;// Creats a DHT object
dht DHT2;

void setup() {
  Serial.begin(9600);

  //setting the relay pins as output
  pinMode(light1, OUTPUT);
  pinMode(light2, OUTPUT);
  pinMode(fan1, OUTPUT);
  pinMode(light3, OUTPUT);
  pinMode(light4, OUTPUT);
  pinMode(fan2, OUTPUT);
  pinMode(waterPump1, OUTPUT);
  pinMode(waterPump2, OUTPUT);

  //setting the I/O of trigger and echo pin
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);

  //setting up the I/O of W.L.S & DHT11
  pinMode(read1, INPUT);
  pinMode(read2, INPUT);
  pinMode(datp1, INPUT);
  pinMode(datp2, INPUT);

  digitalWrite(light1,HIGH);
  digitalWrite(light2,HIGH);
  digitalWrite(light3,HIGH);
  digitalWrite(light4,HIGH);
  digitalWrite(fan1,HIGH);
  digitalWrite(fan2,HIGH);
  digitalWrite(waterPump1,HIGH);
  digitalWrite(waterPump2,HIGH);
}

void loop()
{

  //bluetooth hc05
  
  while(Serial.available()){
  int bt = Serial.read();
 
  if (bt == 65)
  {
    digitalWrite(light1, LOW);
  }
  else if (bt == 66)
  {
    digitalWrite(light1, HIGH);
  }
  else if(bt == 67)
  {
    digitalWrite(light2,LOW);
  }
  else if(bt == 68)
  {
    digitalWrite(light2,HIGH);
  }
  else if(bt == 69)
  {
    digitalWrite(fan1,LOW);
  }
  else if(bt == 70)
  {
    digitalWrite(fan1,HIGH);
  }
  else if(bt == 71)
  {
    digitalWrite(light3,LOW);
  }
  else if(bt == 72)
  {
    digitalWrite(light3,HIGH);
  }
  else if(bt == 73)
  {
    digitalWrite(light4,LOW);
  }
  else if(bt == 74)
  {
    digitalWrite(light4,HIGH);
  }
  else if(bt == 75)
  {
    digitalWrite(fan2,LOW);
  }
  else if(bt == 76)
  {
    digitalWrite(fan2,HIGH);
  }
  else if(bt == 77) 
  {
  digitalWrite(light1,HIGH);
  digitalWrite(light2,HIGH);
  digitalWrite(light3,HIGH);
  digitalWrite(light4,HIGH);
  digitalWrite(fan1,HIGH);
  digitalWrite(fan2,HIGH);
  }
  }
  //wls1
  Value1 = analogRead(read1); //Read data from analog pin and store it to value variable
  Serial.print("wls1 = ");
  Serial.println(Value1);
  if (Value1 > 400 && Value1 <= 700)
  {

    digitalWrite(waterPump1, HIGH);
  }
  else if (Value1 < 400 && sonar1 > 100) {

    digitalWrite(waterPump1, LOW);
  }

  //wls2
  //Value2 = analogRead(read2); //Read data from analog pin and store it to value variable
  //Serial.print("wls2 = ");
  //Serial.println(Value2);
  //if (Value2 > 400 && Value2 <= 700)
  //{

    //digitalWrite(waterPump2, HIGH);
  //}
  //else if (Value2 < 400 && sonar2 > 100) {

    //digitalWrite(waterPump2, LOW);
  //}

  //dht11
  int readData = DHT1.read11(datp1);
  int readData2 = DHT2.read11(datp2);

  float t1 = DHT1.temperature; // Gets the values of the temperature
  float h1 = DHT1.humidity; // Gets the values of the humidity

  float t2 = DHT2.temperature; // Gets the values of the temperature
  float h2 = DHT2.humidity; // Gets the values of the humidity

  Serial.print("temp = ");
  Serial.println(t1);
  Serial.print("humid = ");
  Serial.println(h1);

  Serial.print("temp = ");
  Serial.println(t2);
  Serial.print("humid = ");
  Serial.println(h2);
  
  SonarSensor(trig1, echo1);
  sonar1 = distance;
  //SonarSensor(trig2, echo2);
  //sonar2 = distance;
  Serial.print("Sonar 1 = ");
  Serial.println(sonar1);
  Serial.print("Sonar 2 = ");
  Serial.println(sonar2);
 
  
}

void SonarSensor(int trigPin, int echoPin)
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1;

}
