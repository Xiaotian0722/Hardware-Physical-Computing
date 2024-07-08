// declare
const int sensorEcho = 6; // ultrasonic sensor, listen reflected sound
const int sensorTrig = 7; // ultrasonic sensor, send soundwave

int LEDred = 8; // LED lights
int LEDyellow = 9;
int LEDgreen = 10;

#include <Servo.h> // servo library 
Servo wingRight; // create servo object to control servo
Servo wingLeft;

int wingPos = 0; // variable to store servo position

void setup() {
  // initiate
  pinMode(sensorEcho, INPUT);
  pinMode(sensorTrig, OUTPUT);

  Serial.begin(9600); // start serial communication sensor

  pinMode(LEDred, OUTPUT);
  pinMode(LEDyellow, OUTPUT);
  pinMode(LEDgreen, OUTPUT);

  wingRight.attach(5); // attach the servo on pin to the servo object
  wingLeft.attach(3);
}

void loop() {
  // ultrasonic sensor, send soundwave
  digitalWrite(sensorTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(sensorTrig, HIGH);
  delayMicroseconds(5);
  digitalWrite(sensorTrig, LOW); // wait for the echo

  long duration = pulseIn(sensorEcho, HIGH);
  int cm = duration / 29 / 2; // convert echo time into distance, speed of sound (29 ms/cm) puls travelled forth and back (/2)

  Serial.print(cm);
  Serial.println("cm"); // print value

  

  // close distance
  if (cm < 100) {
    digitalWrite(LEDred, HIGH);
    digitalWrite(LEDyellow, LOW);
    digitalWrite(LEDgreen, LOW);

    // flap wings up and down
    for (wingPos = 60; wingPos <= 180; wingPos += 1) { // goes from 60 degrees to 120 degrees in steps of 1 degree
      wingRight.write(180 - wingPos); // moving symmetrical
      wingLeft.write(wingPos); // tell servo to go to position in variable 'pos'
      delay(5); // wait for the servo to reach the position
    }
    for (wingPos = 180; wingPos >= 60; wingPos -= 1) {
      wingRight.write(180 - wingPos);
      wingLeft.write(wingPos);
      delay(5);
    }
    // play sound
  int frequency = map(cm, 10, 100, 1000, 200); // map distance to frequency
  tone(11, frequency, 500); // play sound, tone(pin, frequency, duration);
  }

  // medium distance
  else if (cm > 100 && cm < 180) {
    digitalWrite(LEDred, LOW);
    digitalWrite(LEDyellow, HIGH);
    digitalWrite(LEDgreen, LOW);
    
    // flap wings up and down (slow)
    for (wingPos = 60; wingPos <= 180; wingPos += 1) { // goes from 60 degrees to 120 degrees in steps of 1 degree
      wingRight.write(180 - wingPos); // moving symmetrical
      wingLeft.write(wingPos); // tell servo to go to position in variable 'pos'
      delay(10); // wait for the servo to reach the position
    }
    for (wingPos = 180; wingPos >= 60; wingPos -= 1) {
      wingRight.write(180 - wingPos);
      wingLeft.write(wingPos);
      delay(10);
    }
  }

  // far distance
  else {
    digitalWrite(LEDred, LOW);
    digitalWrite(LEDyellow, LOW);
    digitalWrite(LEDgreen, HIGH);
  }

  delay(500);
}