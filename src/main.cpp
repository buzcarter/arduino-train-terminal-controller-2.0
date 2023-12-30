#include <Arduino.h>

const int LEFT = 0;
const int RIGHT = 1;

const int SENSOR_THRESHOLD = 500;

int travelDirection;

bool isAtStation(int voltage)
{
  return voltage < SENSOR_THRESHOLD;
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
  digitalWrite(5, LOW);
  digitalWrite(6, LOW);
}

void resumeTravel(int direction)
{
  travelDirection = direction;
  digitalWrite(5, direction == LEFT ? HIGH : LOW);
  digitalWrite(6, direction == RIGHT ? HIGH : LOW);
}

void setup()
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(3, OUTPUT); // control pin of the motor driver
}

void loop()
{
  int terminus1 = analogRead(A0);
  int terminus2 = analogRead(A1);
  int midStation1 = analogRead(A2);

  int currentSpeed = getSpeed();

  analogWrite(3, currentSpeed);

  Serial.println(travelDirection);
  Serial.println(currentSpeed);

  delay(200);

  if (isAtStation(terminus1))
  {
    stopTrain();
    delay(5000);
    resumeTravel(LEFT);
    delay(1500);
  }

  if (isAtStation(terminus2))
  {
    stopTrain();
    delay(5000);
    resumeTravel(RIGHT);
    delay(1500);
  }

  if (isAtStation(midStation1))
  {
    stopTrain();
    delay(5000);
    resumeTravel(travelDirection);
    delay(1500);
  }
}
