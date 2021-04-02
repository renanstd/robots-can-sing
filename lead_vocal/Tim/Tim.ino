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


void setup() {
    for (int i=0; i<sizeof(melody); i++) {
        tone(BUZZER_PIN, melody[i].note, melody[i].duration);
        delay(melody[i].duration);
    }
}


void loop() {
}
