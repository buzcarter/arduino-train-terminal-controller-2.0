#include <Arduino.h>

int station1; // End Station 1
int station2; // End Station 2
int station3; // Middle Station

int Speed; // actualSpeed
int Direction; // travelDirection
int speedval; // adjustedSpeed

void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT); // control pin of the motor driver
}

void loop() {
  // IR proximity sensors
  station1 = analogRead(A0);
  station2 = analogRead(A1);
  station3 = analogRead(A2);

  speedval = analogRead(A3); // potentiometer
  Speed = map(speedval, 0, 1023, 0, 255); // analog reader is 10bit, PWM Timer is 8bit

  analogWrite(3, Speed);
  Serial.println(Direction);
  Serial.println(Speed);
  delay(200);

  // midpoint of a sensor being tripped ~500
  if (station1 < 500) {
    // train is in front of End Station 1's sensor

    // stop sending power to the track
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);

    Direction = 0;
    
    // sit idle for 5 seconds
    delay(5000);
    // start moving in the "0" direction
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    delay(1500);
  }
  
  if (station2 < 500) {
    // train is in front of End Station 2's sensor

    // stop sending power to the track
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);

    // reverse direction
    Direction = 1;
    
    delay(5000);

    // start moving in the "1" direction
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
  }
  
  // Stations located around the middle of the track
  // for these we'll just pause for a moment before continuing on our way (same direction)
  if (station3 < 500 && Direction == 1) {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    
    delay(5000);
    
    digitalWrite(5, LOW);
    digitalWrite(6, HIGH);
    
    delay(1500);
  }

  if (station3 < 500 && Direction == 0) {
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    
    delay(5000);
    
    digitalWrite(5, HIGH);
    digitalWrite(6, LOW);
    
    delay(1500);
  }
}
