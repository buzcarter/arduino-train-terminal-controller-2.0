#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>
#include <msgMgr.h>
#include <speedMgr.h>
#include <stationMgr.h>
#include <TaskScheduler.h>

const int MAIN_TASKS_INTERVAL = 200;
const int INFO_TASKS_INTERVAL = 1000;
const int SPEED_SAMPLING_INTERVAL = 50;

Scheduler taskRunner;

void checkStationsTask();

Task t0(CLOCKIE_INTERVAL, TASK_FOREVER, &updateClockIndicator, &taskRunner, true);
Task t1(MAIN_TASKS_INTERVAL, TASK_FOREVER, &checkStationsTask, &taskRunner, true);
Task t2(INFO_TASKS_INTERVAL, TASK_FOREVER, &updateSpeed, &taskRunner, true);
Task t3(MAIN_TASKS_INTERVAL, TASK_FOREVER, &msgSendSpeedInfo, &taskRunner, true);
Task t4(SPEED_SAMPLING_INTERVAL, TASK_FOREVER, &sampleSpeed, &taskRunner, true);

void checkStationsTask()
{
  if (!pendingActionsResolved())
  {
    return;
  }

  if (isAtTerminus())
  {
    reverseDirection();
  }
  else if (isAtMiddleStation())
  {
    pauseAndResume();
  }
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
  if (!isLEDTestDone())
  {
    return;
  }
  taskRunner.execute();
}
