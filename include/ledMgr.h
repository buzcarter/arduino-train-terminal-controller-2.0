/** what proportion of the blink interval should the clock be on? 3 = 1/3 of 1 second */
const int CLOCKIE_ON_RATIO = 3;
/** ticks between time checks */
const int CLOCK_LED_PULSE_INTERVAL = 1000 / CLOCKIE_ON_RATIO ;

bool isLEDTestDone();
void updateDirectionLED(int direction);
void updateLayoverLED(bool isStopped);
void updateSpeedLEDs(int speed);
void updateClockLED();
