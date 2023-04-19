# 04_19

## 1. Timer1

|함수|기능|설명|
|------|:---:|---|
|Timer1.initialize()|Timer1 초기화||
|Timer1.pwm()|핀에 사각 파형 생성|Timer1.pwm(pin, duty)<br>duty : 0~1023|
|Timer1.setPeriod()|마이크로초 단위로 주기 설정|Timer1.setPeriod(1000000) : 1Hz<br>Timer1.setPeriod(1000000/10) : 10Hz|
|Timer1.setPwmDuty(pin,duty)|핀에 사각 파형의 duty 설정|Timer1.setPwmDuty(LED, 511) : 중간<br>Timer1.setPwmDuty(LED, 100) : 어두움<br>Timer1.setPwmDuty(LED, 900) : 밝음<br>Timer1.setPwmDuty(SERVO, angle)|

여기서 Timer1.setPwmDuty를 더 자세히 설명하자면 여기서 duty값은 HIGH의 개수를 뜻합니다. 0~1023 값이 들어갈 수 있습니다. 예를 들어 Timer1.setPwmDuty(LED, 511)라면 511 동안 HIGH를 유지하고 512(1023-511) 동안 LOW를 유지하는 LED Blink를 구현할 수 있습니다. Timer1.setPwmDuty(LED, 900)이라면 900 동안 HIGH에 123 동안 LOW인 상태로 LED가 점멸할 것이고 이를 통해 LED의 밝기를 조절할 수 있습니다.
