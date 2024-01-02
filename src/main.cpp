#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>
#include <speedMgr.h>
#include <stationMgr.h>
#include <TaskScheduler.h>

const int TASK_FREQUENCY = 200; // ms

void checkStationsTask();
void updateSpeedTask();
void sendFeedbackTask();

Scheduler taskRunner;

Task stationTask(TASK_FREQUENCY, TASK_FOREVER, &checkStationsTask, &taskRunner, true);
Task speedTask(TASK_FREQUENCY, TASK_FOREVER, &updateSpeedTask, &taskRunner, true);
Task feedbackTask(TASK_FREQUENCY, TASK_FOREVER, &sendFeedbackTask, &taskRunner, true);

void checkStationsTask()
{
  if (isAtTerminus())
  {
    stationTask.disable();
    reverseDirection();
    stationTask.enable();
  }
  else if (isAtMiddleStation())
  {
    stationTask.disable();
    pauseAndResume();
    stationTask.enable();
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

void setup()
{
  Serial.begin(9600);
  pinMode(MOTOR_FORWARD_OUT, OUTPUT);
  pinMode(MOTOR_REVERSE_OUT, OUTPUT);
  pinMode(MOTOR_SPEED_OUT, OUTPUT);

  pinMode(CLOCK_LED_OUT, OUTPUT);

  pinMode(FORWARD_LED_OUT, OUTPUT);
  pinMode(LAYOVER_LED_OUT, OUTPUT);

  pinMode(SPEED_MIN_LED_OUT, OUTPUT);
  pinMode(SPEED_20_LED_OUT, OUTPUT);
  pinMode(SPEED_40_LED_OUT, OUTPUT);
  pinMode(SPEED_80_LED_OUT, OUTPUT);
  pinMode(SPEED_MAX_LED_OUT, OUTPUT);
}

void loop()
{
  if (startUpTest())
  {
    return;
  }

  toggleClockTickIndicator();
  taskRunner.execute();
}
