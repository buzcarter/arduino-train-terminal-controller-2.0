#include <Arduino.h>

#define ON   HIGH
#define OFF  LOW

const int FORWARD  = 0;
const int REVERSE  = 1;

// Arduino (Output) Digital PWM Pins to Motor Driver
const int MOTOR_SPEED_OUT       = 3;
const int MOTOR_FORWARD_OUT     = 5;
const int MOTOR_REVERSE_OUT     = 6;

// LED Output Pins
const int FORWARD_LED_OUT       = 4;
const int LAYOVER_LED_OUT       = 7;

const int CLOCK_LED_OUT         = 8;

const int SPEED_MIN_LED_OUT     = 9;
const int SPEED_20_LED_OUT      = 10;
const int SPEED_40_LED_OUT      = 11;
const int SPEED_80_LED_OUT      = 12;
const int SPEED_MAX_LED_OUT     = 13;

// Arduino Analog Input Pins from IR proximity sensors
const uint8_t TERMINUS_1_INPUT    = A0;
const uint8_t TERMINUS_2_INPUT    = A1;
const uint8_t MID_STATION_1_INPUT = A2;

const uint8_t POTENTIOMETER_INPUT = A3;

/** Cutoff for IR proximity filter */
const int SENSOR_THRESHOLD = 500;
