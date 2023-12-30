#include <Arduino.h>
#include <TaskScheduler.h>
#include <constants.h>
#include <speedMgr.h>
#include <stationMgr.h>

void checkStationsTask()
{
  if (isAtTerminus())
  {
    reverseDirection();
  }
  else if (isAtMiddleStation())
  {
    pauseAndResume();
  }
}

void updateSpeedTask()
{
  updateSpeed();
}

void sendFeedbackTask()
{
  Serial.println("Speed: " + String(getSpeed()) + " " + getDirection());
}

Scheduler taskRunner;

Task stationTask(TASK_FREQUENCY, TASK_FOREVER, &checkStationsTask, &taskRunner, true);
Task speedTask(TASK_FREQUENCY, TASK_FOREVER, &updateSpeedTask, &taskRunner, true);
Task feedbackTask(TASK_FREQUENCY, TASK_FOREVER, &sendFeedbackTask, &taskRunner, true);

void setup()
{
  Serial.begin(9600);
  pinMode(MOTOR_FORWARD, OUTPUT);
  pinMode(MOTOR_REVERSE, OUTPUT);
  pinMode(MOTOR_SPEED, OUTPUT);
}

void loop()
{
  taskRunner.execute();
}
