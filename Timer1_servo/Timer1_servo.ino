#include <TimerOne.h>

const int sev = 10;
const int period = 20000;
const int minduty = (1024 / 20) * 0.7;
const int maxduty = (1024 / 20) * 2.3;
int angle = minduty;

void setup() {
  Serial.begin(9600);
  Timer1.initialize();
  Timer1.pwm(sev, 0);
  Timer1.setPeriod(period);
}

void loop() {
  if (Serial.available() > 0) {                         // 시리얼 입력값이 존재할 경우
    int input = Serial.parseInt();                      // 입력값을 정수형으로 변환합니다.
    if (input >= 0 && input <= 180) {                   // 입력값이 0부터 180 사이일 경우
      int duty = map(input, 0, 180, minduty, maxduty);  // 입력값을 듀티 사이클로 변환합니다.
      while (angle != duty) {                           // 현재 각도와 듀티 사이클이 같아질 때까지 반복합니다.
        Serial.println((String) "angle : " + angle);
        Serial.println((String) "duty : " + duty);
        if (angle < duty) {
          angle++;  // 현재 각도가 듀티 사이클보다 작을 경우 각도를 증가시킵니다.
        } else {
          angle--;  // 현재 각도가 듀티 사이클보다 클 경우 각도를 감소시킵니다.
        }
        // Timer1.setPwmDuty(sev, angle);  // 서보 모터를 현재 각도로 돌립니다.
        delay(30);
      }
    }
  }
}