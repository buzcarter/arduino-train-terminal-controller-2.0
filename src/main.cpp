#include <Arduino.h>
#include <constants.h>
#include <ledMgr.h>
#include <speedMgr.h>
#include <stationMgr.h>
#include <TaskScheduler.h>

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

void clockie() {
  static int flashTick = 0;
  flashTick++;
  digitalWrite(CLOCK_LED_OUT, flashTick % 3 == 0 ? ON : OFF);
}

Scheduler taskRunner;

Task stationTask(333, TASK_FOREVER, &clockie, &taskRunner, true);

void loop()
{
  taskRunner.execute();

  // static bool isOn = false;
  // isOn = !isOn;
  // int value = isOn ? LOW : HIGH;


  // digitalWrite(FORWARD_LED_OUT, value);
  // digitalWrite(LAYOVER_LED_OUT, value);

  // digitalWrite(SPEED_MIN_LED_OUT, ON);
  // digitalWrite(SPEED_20_LED_OUT, ON);
  // digitalWrite(SPEED_40_LED_OUT, ON);
  // digitalWrite(SPEED_80_LED_OUT, ON);
  // digitalWrite(SPEED_MAX_LED_OUT, ON);

  // delay(100);
}
