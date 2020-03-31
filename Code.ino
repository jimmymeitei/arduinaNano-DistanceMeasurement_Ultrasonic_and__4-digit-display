
#define TriggerPin  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define EchoPin     9  // Arduino pin tied to echo pin on the ultrasonic sensor.

////////////////////////////
#include <Arduino.h>
#include <TM1637Display.h>

// Module connection pins (Digital Pins)
#define CLK 2
#define DIO 3
// The amount of time (in milliseconds) between tests
TM1637Display display(CLK, DIO);
/////////////////////////
long Duration = 0;

void setup() {
  pinMode(TriggerPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  Serial.begin(9600); // Open serial monitor at 9600 baud
}

void loop() {

  digitalWrite(TriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TriggerPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(TriggerPin,LOW);

  Duration = pulseIn(EchoPin, HIGH);
  long Distance_cm = Distance(Duration);
  Serial.print("Distance = ");
  Serial.print(Distance_cm);
  Serial.print(" cm \n");

  delay(300);
  //Display
  display.setBrightness(0x0f);
  uint8_t data[] = { 0x0, 0x0, 0x0, 0x0 };
  display.setSegments(data);
 
  display.showNumberDec(Distance_cm, false, 4,0);
  delay(300);  
}
long Distance(long time)
{
  long DistanceCal;

  DistanceCal = ((time * 0.034) / 2);
  return DistanceCal;
}
 
