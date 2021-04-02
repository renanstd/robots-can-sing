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
    {NOTE_CS5, 8, 1, 1},
    {NOTE_CS5, 8, 1, 1},
    {NOTE_DS5, 8, 1, 1},
    {NOTE_DS5, 8, 1, 1},
    {NOTE_CS5, 8, 1, 1},
    {NOTE_CS5, 8, 1, 1},
    {NOTE_DS5, 8, 1, 1},
    {NOTE_DS5, 8, 1, 1},
    {REST, 8, 1, 1},
};

// Calcula a quantidade de movementos da melodia
int notes = sizeof(melody)/sizeof(melody[0]);
int wholenote = (60000 * 4) / TEMPO;
int divider = 0, note_duration = 0;

void setup() {
    Serial.begin(9600);

    for (int i=0; i<=notes; i++) {
        // Armazena o movimento atual em uma variável
        Movement movement = melody[i];
        divider = movement.duration;

        // Verifica se é uma nota pontuada
        if (divider > 0) {
            note_duration = (wholenote) / divider;
        } else if (divider < 0) {
            note_duration = (wholenote) / abs(divider);
            note_duration *= 1.5;
        }

        // Toca a nota
        tone(BUZZER_PIN, movement.note, note_duration * 0.9);
        delay(note_duration);
        noTone(BUZZER_PIN);
    }
}


void loop() {
}
