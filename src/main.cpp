#include <Arduino.h>

const int FORWARD = 0;
const int REVERSE = 1;

const int DRIVER_A_FORWARD = 5;
const int DRIVER_A_REVERSE = 6;
const int DRIVER_A_OUTPUT_LEVEL = 3;

const uint8_t TERMINUS_1_PIN = A0;
const uint8_t TERMINUS_2_PIN = A1;
const uint8_t MID_STATION_1_PIN = A2;

#define ON HIGH
#define OFF LOW

/** Cutoff for IR proximity filter */
const int SENSOR_THRESHOLD = 500;

int travelDirection;

bool isAtStation(int sensorValue)
{
  return sensorValue < SENSOR_THRESHOLD;
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

void stopTrain()
{
  digitalWrite(DRIVER_A_FORWARD, OFF);
  digitalWrite(DRIVER_A_REVERSE, OFF);
}

void resumeTravel(int direction)
{
  travelDirection = direction;
  digitalWrite(DRIVER_A_FORWARD, direction == FORWARD ? ON : OFF);
  digitalWrite(DRIVER_A_REVERSE, direction == REVERSE ? ON : OFF);
}

void stopAndGo(int direction)
{
  stopTrain();
  delay(5000);
  resumeTravel(direction);
  delay(1500);
}

void setup()
{
  Serial.begin(9600);
  pinMode(DRIVER_A_FORWARD, OUTPUT);
  pinMode(DRIVER_A_REVERSE, OUTPUT);
  pinMode(DRIVER_A_OUTPUT_LEVEL, OUTPUT);
}

void loop()
{
  int terminus1 = analogRead(TERMINUS_1_PIN);
  int terminus2 = analogRead(TERMINUS_2_PIN);

  int midStation1 = analogRead(MID_STATION_1_PIN);

  int currentSpeed = getSpeed();

  analogWrite(DRIVER_A_OUTPUT_LEVEL, currentSpeed);

  Serial.println(travelDirection);
  Serial.println(currentSpeed);

  delay(200);

  if (isAtStation(terminus1))
  {
    stopAndGo(REVERSE);
  }
  else if (isAtStation(terminus2))
  {
    stopAndGo(FORWARD);
  }
  else if (isAtStation(midStation1))
  {
    stopAndGo(travelDirection);
  }
}
