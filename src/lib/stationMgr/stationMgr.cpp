#include <Arduino.h>
#include <constants.h>

int trainDirection;

/**
 * Check if the train is at a station by reading the IR proximity sensor
 * (corresponding to `pin`) and comparing it to the threshold.
 */
bool isAtStation(uint8_t pin)
{
  return analogRead(pin) < SENSOR_THRESHOLD;
}

bool isAtTerminus()
{
  return isAtStation(TERMINUS_1) || isAtStation(TERMINUS_2);
}

/**
 * Makes adding additional stations easier, just OR ('||') them together
 */
bool isAtMiddleStation()
{
  return isAtStation(MID_STATION_1);
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
  delay(5000); // ideally wouldn't block, but this is a simple example
  startTrain(direction);
}

void reverseDirection()
{
  stopAndGo(trainDirection == FORWARD ? REVERSE : FORWARD);
}

void pauseAndResume()
{
  stopAndGo(trainDirection);
}

String getDirection()
{
  return (trainDirection == FORWARD) ? "forward" : "reverse";
}
