#include "pitches.h"


const int TEMPO = 140;
const int BUZZER_PIN = 11;

struct Movement {
    int note;
    float duration;
    int mouth_movement;
    int expression;
};

Movement melody[] = {
    // Intro
    {NOTE_CS5, 8, 1, 1},
    {NOTE_CS5, 8, 1, 1},
    {NOTE_DS5, 8, 1, 1},
    {NOTE_DS5, 8, 1, 1},
};

int notes = sizeof(melody)/sizeof(melody[0]);

void setup() {
    Serial.begin(9600);

    for (int i=0; i<=notes; i++) {
        Movement mov = melody[i];
        tone(BUZZER_PIN, mov.note);
        tone(BUZZER_PIN, mov.note, mov.duration);
        delay(mov.duration);
    }
}


void loop() {
}
