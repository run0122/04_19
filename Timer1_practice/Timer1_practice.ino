#include <TimerOne.h>

const int LED = 9;

void setup() {
  Timer1.initialize();
  Timer1.pwm(LED, 0);

  Timer1.setPeriod(1000000/1000);
  Timer1.setPwmDuty(LED, 900);
}

void loop() {
  // put your main code here, to run repeatedly:
}
