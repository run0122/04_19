# 04_19

## 1. Timer1

|함수|기능|설명|
|------|:---:|---|
|Timer1.initialize()|Timer1 초기화||
|Timer1.pwm()|핀에 사각 파형 생성|Timer1.pwm(pin, duty)<br>duty : 0~1023|
|Timer1.setPeriod()|마이크로초 단위로 주기 설정|Timer1.setPeriod(1000000) : 1Hz<br>Timer1.setPeriod(1000000/10) : 10Hz|
|Timer1.setPwmDuty(pin,duty)|핀에 사각 파형의 duty 설정|Timer1.setPwmDuty(LED, 511) : 중간<br>Timer1.setPwmDuty(LED, 100) : 어두움<br>Timer1.setPwmDuty(LED, 900) : 밝음<br>Timer1.setPwmDuty(SERVO, angle)|

Timer1.setPwmDuty를 더 자세히 설명하자면 여기서 duty값은 HIGH의 개수를 뜻합니다. 0~1023 값이 들어갈 수 있습니다. 

예를 들어 Timer1.setPwmDuty(LED, 511)라면 511 동안 HIGH를 유지하고 512(1023-511) 동안 LOW를 유지하는 LED Blink를 구현할 수 있습니다. 

Timer1.setPwmDuty(LED, 900)이라면 900 동안 HIGH에 123 동안 LOW인 상태로 LED가 점멸할 것입니다. 이를 통해 LED의 밝기를 조절할 수 있습니다.

## 2. Linetracer -> PWM 변환

라인트레이서의 digitalWrite와 analogWrite를 통한 속도 제어 부분을 PWM으로 변환했습니다. 실습을 통해서 9번 핀과 10번 핀의 위치만 PWM이 적용된다는 사실을 파악하였고, 이에 맞게 점퍼선의 위치를 바꿔줬습니다.

라인트레이서 전면부의 조도센서 값을 통해서 LED와 버저가 작동하도록 하였고, millis를 통해서 동시에 작동하도록 했습니다.

현재 라인트레이서의 최종 코드는 Timer1_car 입니다.
