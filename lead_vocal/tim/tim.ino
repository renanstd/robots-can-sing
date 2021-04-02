#include "pitches.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>


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
    {NOTE_CS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_DS6, 8, 1, 1},
    {NOTE_DS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_DS6, 8, 1, 1},
    {NOTE_DS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_DS6, 8, 1, 1},
    {NOTE_DS6, 2, 1, 1},
    {REST, 4, 1, 1},

    {NOTE_CS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_DS6, 8, 1, 1},
    {NOTE_DS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_DS6, 8, 1, 1},
    {NOTE_DS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_DS6, 8, 1, 1},
    {NOTE_DS6, 2, 1, 1},
    {REST, 4, 1, 1},

    {NOTE_CS6, 8, 1, 1},
    {NOTE_CS6, 8, 1, 1},
    {NOTE_C6, 8, 1, 1},
    {NOTE_C6, 8, 1, 1},
    {NOTE_AS5, 8, 1, 1},
    {NOTE_AS5, 8, 1, 1},
    {NOTE_GS5, 8, 1, 1},
    {NOTE_AS5, 8, 1, 1},
    {NOTE_GS5, 8, 1, 1},
    {NOTE_GS5, 8, 1, 1},
    {NOTE_AS5, 8, 1, 1},
    {NOTE_GS5, 2, 1, 1},
    {REST, 8, 1, 1},

    // Timmy
    {NOTE_GS7, 4, 2, 2},
    {NOTE_CS8, 8, 3, 1},
    {NOTE_AS7, 2, 2, 3},
};

// Calcula a quantidade de movementos da melodia
int notes = sizeof(melody)/sizeof(melody[0]);
int wholenote = (60000 * 4) / TEMPO;
int divider = 0, note_duration = 0;

// Inicializa display e servo
Adafruit_SSD1306 display = Adafruit_SSD1306();
Servo servo;

void animate_mouth(int mouth_movement) {
    if (mouth_movement == 2) {
        display.clearDisplay();
        display.fillRect(30, 12, 10, 2, WHITE);
        display.fillRect(90, 12, 10, 2, WHITE);
        display.fillCircle(65, 25, 4, WHITE);
        display.display();
    } else if (mouth_movement == 3) {
        display.clearDisplay();
        display.fillRect(30, 12, 10, 2, WHITE);
        display.fillRect(90, 12, 10, 2, WHITE);
        display.fillCircle(65, 25, 6, WHITE);
        display.display();
    }
}

void play_expression(int expression) {
    if (expression == 2) {
        servo.write(80);
    } else if (expression == 3) {
        servo.write(100);
    }
}

void setup() {
    servo.attach(3);
    servo.write(90);
    Wire.begin();
    display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

    display.clearDisplay();
    display.fillRect(30, 8, 10, 20, WHITE);
    display.fillRect(90, 8, 10, 20, WHITE);
    display.fillRect(34, 18, 6, 4, BLACK);
    display.fillRect(94, 18, 6, 4, BLACK);
    display.drawLine(60, 31, 70, 31, WHITE);
    display.display();

    for (int i=0; i<=notes; i++) {
        // Armazena o movimento atual em uma variável
        Movement movement = melody[i];
        divider = movement.duration;

        // Anima a boca do personagem
        animate_mouth(movement.mouth_movement);
        play_expression(movement.expression);

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

    display.clearDisplay();
    display.fillRect(30, 8, 10, 20, WHITE);
    display.fillRect(90, 8, 10, 20, WHITE);
    display.fillRect(34, 18, 6, 4, BLACK);
    display.fillRect(94, 18, 6, 4, BLACK);
    display.drawLine(60, 31, 70, 31, WHITE);
    display.display();

    servo.write(90);
}


void loop() {
}
