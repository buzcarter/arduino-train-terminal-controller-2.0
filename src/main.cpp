#include <Arduino.h>

const int FORWARD = 0;
const int REVERSE = 1;

// Arduinao (Output) Digital PWM Pins to Motor Driver
const int MOTOR_FORWARD = 5;
const int MOTOR_REVERSE = 6;
const int MOTOR_SPEED = 3;

// Arduino Analog Input Pins from IR proximity sensors
const uint8_t TERMINUS_1 = A0;
const uint8_t TERMINUS_2 = A1;
const uint8_t MID_STATION_1 = A2;

#define ON HIGH
#define OFF LOW

/** Cutoff for IR proximity filter */
const int SENSOR_THRESHOLD = 500;

int trainDirection;
int trainSpeed;

bool isAtStation(uint8_t pin)
{
  return analogRead(pin) < SENSOR_THRESHOLD;
}

/**
 * Get desired speed from the potentiometer.
 * Makes adjustments to address disparity between analog read (10 bit)
 * and analog write (8 bit)
 */
int getSpeed()
{
  int potValue = analogRead(A3);
  return map(potValue, 0, 1023, 0, 255);
}

void updateSpeed()
{
  trainSpeed = getSpeed();
  analogWrite(MOTOR_SPEED, trainSpeed);
}

void stopTrain()
{
  digitalWrite(MOTOR_FORWARD, OFF);
  digitalWrite(MOTOR_REVERSE, OFF);
}

void startTrain(int direction)
{
  trainDirection = direction;
  digitalWrite(MOTOR_FORWARD, direction == FORWARD ? ON : OFF);
  digitalWrite(MOTOR_REVERSE, direction == REVERSE ? ON : OFF);
}

void stopAndGo(int direction)
{
  stopTrain();
  delay(5000);
  startTrain(direction);
  delay(1500);
}

void reverseDirection()
{
  stopAndGo(trainDirection == FORWARD ? REVERSE : FORWARD);
}

void pauseAndResume()
{
  stopAndGo(trainDirection);
}

void reportStatus()
{
  Serial.println("Speed: " + String(trainSpeed) + " " + (trainDirection == FORWARD) ? "forward" : "reverse");
}

void setup()
{
  Serial.begin(9600);
  pinMode(MOTOR_FORWARD, OUTPUT);
  pinMode(MOTOR_REVERSE, OUTPUT);
  pinMode(MOTOR_SPEED, OUTPUT);
}

void loop()
{
  updateSpeed();
  reportStatus();
  delay(200);

  if (isAtStation(TERMINUS_1) || isAtStation(TERMINUS_2))
  {
    reverseDirection();
  }
  else if (isAtStation(MID_STATION_1))
  {
    pauseAndResume();
  }
}
