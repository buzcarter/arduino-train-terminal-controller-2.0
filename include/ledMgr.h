const int CLOCKIE_ON_RATIO = 3;
const int CLOCKIE_INTERVAL = 1000 / CLOCKIE_ON_RATIO ;

bool isLEDTestDone();
void showDirection(int direction);
void showLayover(bool isStopped);
void showSpeed(int speed);
void updateClockIndicator();
