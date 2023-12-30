#include <Arduino.h>

#define ON HIGH
#define OFF LOW

const int FORWARD = 0;
const int REVERSE = 1;

// Arduino (Output) Digital PWM Pins to Motor Driver
const int MOTOR_FORWARD = 5;
const int MOTOR_REVERSE = 6;
const int MOTOR_SPEED = 3;

// Arduino Analog Input Pins from IR proximity sensors
const uint8_t TERMINUS_1 = A0;
const uint8_t TERMINUS_2 = A1;
const uint8_t MID_STATION_1 = A2;

const uint8_t POTENTIOMETER = A3;

/** Cutoff for IR proximity filter */
const int SENSOR_THRESHOLD = 500;
