#include <TimerOne.h>

// 기본 모터 & IR 핀

// const int motor_A1 = 5;
// const int motor_A2 = 6;
// const int motor_B1 = 10;
// const int motor_B2 = 11;

const int motor_A1 = 9;
const int motor_A2 = 8;
const int motor_B1 = 10;
const int motor_B2 = 11;


const int IR_R = A1;
const int IR_M = A3;
const int IR_L = A5;
int IR_L_data;
int IR_M_data;
int IR_R_data;

// LED

const int led1 = 12;
const int led2 = 13;

int ledState = LOW;

// drive_Log 시작 종료 조건

bool startCheck = false;
bool finishCheck = true;

// drive_Log

unsigned long startTime = 0;
unsigned long finishTime = 0;

// IR data interval

unsigned long previousMillis = 0;
const long interval = 100;

// LED interval

unsigned long previousledMillis = 0;
const long ledinterval = 1000;

// button

const int button = 2;
bool driveState = false;

int buttonState;
int lastButtonState = LOW;

unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

// photo

int photo = A7;
int photoData;

// setup

void setup() {
  pinMode(motor_A1, OUTPUT);
  pinMode(motor_A2, OUTPUT);
  pinMode(motor_B1, OUTPUT);
  pinMode(motor_B2, OUTPUT);
  pinMode(IR_L, INPUT);
  pinMode(IR_M, INPUT);
  pinMode(IR_R, INPUT);
  Serial.begin(9600);
  Serial.println("Start");

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(button, INPUT);

  Timer1.initialize();
  Timer1.pwm(motor_A1, 0);
  Timer1.pwm(motor_A2, 0);
  Timer1.pwm(motor_B1, 0);
  Timer1.pwm(motor_B2, 0);

  Timer1.setPeriod(100);
}

void loop() {
  // LED

  // ledOnOff();

  // Button & Drive

  int reading = digitalRead(button);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == HIGH) {
        driveState = !driveState;
      }
    }
  }

  // photo
  photoData = analogRead(photo);

  // if (driveState == true && photoData > 100) {
  //   drive();
  // } else if (driveState == true && photoData < 100) {
  //   stop();
  // } else if (driveState == false) {
  //   stop();
  // }

  if (driveState == true) {
    drive();
  } else if (driveState == false) {
    stop();
  }

  lastButtonState = reading;
}

// LED

void ledOnOff() {
  unsigned long currentledMillis = millis();

  if ((currentledMillis - previousledMillis) >= ledinterval) {

    previousledMillis = currentledMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }
    digitalWrite(led1, ledState);
    digitalWrite(led2, ledState);
  }
}

// 주행

void drive() {
  unsigned long currentMillis = millis();

  IR_L_data = digitalRead(IR_L);
  IR_M_data = digitalRead(IR_M);
  IR_R_data = digitalRead(IR_R);

  if ((currentMillis - previousMillis) >= interval) {

    previousMillis = currentMillis;

    Serial.print(IR_L_data);
    Serial.print("-");
    Serial.print(IR_M_data);
    Serial.print("-");
    Serial.println(IR_R_data);
    Serial.println((String) "photoData : " + photoData);
  }

  if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 0) {
    // 직진
    if (startCheck == false) {
      startCheck = true;
      if (finishCheck == true) {
        finishCheck = false;
      }
      startTime = millis();
      Serial.println("주행 시작");
    }
    forward();
  } else if (IR_L_data == 1 and IR_M_data == 0 and IR_R_data == 0) {
    // 좌회전
    left();
  } else if (IR_L_data == 1 and IR_M_data == 1 and IR_R_data == 0) {
    // 좌회전
    smooth_left();
  } else if (IR_L_data == 0 and IR_M_data == 0 and IR_R_data == 1) {
    // 부드러운 좌
    right();
  } else if (IR_L_data == 0 and IR_M_data == 1 and IR_R_data == 1) {
    // 부드러운 우
    smooth_right();
  } else if (IR_L_data == 1 and IR_M_data == 1 and IR_R_data == 1) {
    // 정지
    stop();
    if (startCheck == true) {
      startCheck = false;
      if (finishCheck == false) {
        finishCheck = true;
      }
      finishTime = millis();
      Serial.println("주행 종료");
      ride_log();
    }
  }
}

void right() {
  //우
  Timer1.setPwmDuty(motor_A1, 1023);
  Timer1.setPwmDuty(motor_A2, 0);
  Timer1.setPwmDuty(motor_B1, 0);
  Timer1.setPwmDuty(motor_B2, 0);
}

void left() {
  //좌
  Timer1.setPwmDuty(motor_A1, 0);
  Timer1.setPwmDuty(motor_A2, 0);
  Timer1.setPwmDuty(motor_B1, 1023);
  Timer1.setPwmDuty(motor_B2, 0);
}

void smooth_right() {
  //부드러운 우
  Timer1.setPwmDuty(motor_A1, 1023);
  Timer1.setPwmDuty(motor_A2, 0);
  Timer1.setPwmDuty(motor_B1, 850);
  Timer1.setPwmDuty(motor_B2, 0);
}

void smooth_left() {
  //부드러운 좌
  Timer1.setPwmDuty(motor_A1, 850);
  Timer1.setPwmDuty(motor_A2, 0);
  Timer1.setPwmDuty(motor_B1, 1023);
  Timer1.setPwmDuty(motor_B2, 0);
}

void forward() {
  //전진
  Timer1.setPwmDuty(motor_A1, 1023);
  Timer1.setPwmDuty(motor_A2, 0);
  Timer1.setPwmDuty(motor_B1, 1023);
  Timer1.setPwmDuty(motor_B2, 0);
}

void backward() {
  //후진
  Timer1.setPwmDuty(motor_A1, 0);
  Timer1.setPwmDuty(motor_A2, 1023);
  Timer1.setPwmDuty(motor_B1, 0);
  Timer1.setPwmDuty(motor_B2, 1023);
}

void stop() {
  //정지
  Timer1.setPwmDuty(motor_A1, 0);
  Timer1.setPwmDuty(motor_A2, 0);
  Timer1.setPwmDuty(motor_B1, 0);
  Timer1.setPwmDuty(motor_B2, 0);
}

void ride_log() {
  if ((finishTime - startTime) > 100) {
    Serial.println((String)(finishTime - startTime) + " 동안 주행 하였음.");
  }
}