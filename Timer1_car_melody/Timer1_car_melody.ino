#include "pitches.h"

int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};

const int buzzer = 7;

int noteIndex = 0;
unsigned long previousTime = 0;
unsigned long noteDuration;

void setup() {
  pinMode(buzzer, OUTPUT);
}

void loop() {
  unsigned long currentTime = millis();

  if (currentTime - previousTime >= noteDuration) {
    int note = melody[noteIndex];
    noteDuration = 1000 / noteDurations[noteIndex];

    if (note != 0) {
      tone(buzzer, note, noteDuration);
    } else {
      noTone(buzzer);
    }

    noteIndex++;
    if (noteIndex >= sizeof(melody)/sizeof(melody[0])) {
      noteIndex = 0;
    }

    previousTime = currentTime;
  }
}