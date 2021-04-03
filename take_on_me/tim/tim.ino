#include "pitches.h"
#include <Wire.h>
#include <Servo.h>
#include<LiquidCrystal_I2C.h>


const int TEMPO = 100;
const int BUZZER_PIN = 11;

struct Movement {
    int note;
    float duration;
    int mouth_movement;
    int expression;
    int vocal;
};

Movement melody[] = {
    {NOTE_E7,  -4, 2, 0, 1},
    {NOTE_E7,  4, 1, 0, 1},
    {NOTE_DS7, 8, 2, 0, 1},
    {NOTE_CS7, -4, 1, 0, 1},
    {REST,     1, 0, 0, 1},

    {NOTE_DS7, 8, 0, 0, 1},
    {NOTE_DS7, 4, 0, 0, 1},
    {NOTE_DS7, 4, 0, 0, 1},
    {NOTE_B6,  4, 0, 0, 1},
    {REST,     4, 0, 0, 1},

    {NOTE_GS7, 8, 0, 0, 1},
    {REST,     4, 0, 0, 1},
    {NOTE_GS7, 4, 0, 0, 1},
    {NOTE_FS7, 4, 0, 0, 1},

    {NOTE_E7, -4, 2, 0, 1},
    {NOTE_E7,  4, 1, 0, 1},
    {NOTE_DS7, 8, 2, 0, 1},
    {NOTE_CS7, -4, 1, 0, 1},
    {REST,     -2, 0, 0, 1},

    {NOTE_CS7, 8, 1, 0, 1},
    {NOTE_DS7, 8, 1, 0, 1},
    {NOTE_DS7, 4, 1, 0, 1},
    {NOTE_DS7, 4, 1, 0, 1},
    {NOTE_CS7, 4, 1, 0, 1},
    {NOTE_B6,  4, 0, 0, 1},
    {NOTE_B6,  4, 0, 0, 1},
    {NOTE_DS7, 8, 1, 0, 1},
    {NOTE_CS7, 4, 1, 0, 1},
    {NOTE_B6,  4, 0, 0, 1},
    {REST,     4, 0, 0, 1},

    {NOTE_E7,  -4, 0, 0, 1},
    {NOTE_E7,  4, 0, 0, 1},
    {NOTE_E7,  -4, 0, 0, 1},
    {REST,     -2, 0, 0, 1},

    {NOTE_B6,  8, 0, 0, 1},
    {NOTE_B6,  8, 0, 0, 1},
    {NOTE_B6,  8, 0, 0, 1},
    {NOTE_B6,  8, 0, 0, 1},
    {NOTE_B6,  8, 0, 0, 1},
    {NOTE_B6,  8, 0, 0, 1},
    {NOTE_B6,  8, 0, 0, 1},
    {NOTE_AS6, 4, 0, 0, 1},
    {NOTE_GS6, 4, 0, 0, 1},
    {NOTE_FS6, 4, 0, 0, 1},
    {REST,     8, 0, 0, 1},

    // Chorus
    {NOTE_B5,  2, 0, 0, 1},
    {REST,     2, 0, 0, 1},
    {NOTE_FS6, 2, 0, 0, 1},
    {REST,     2, 0, 0, 1},
    {NOTE_GS6, 2, 0, 0, 1},
    {REST,     1, 0, 0, 1},
    {REST,     2, 0, 0, 1},

    {NOTE_B5,  2, 0, 0, 1},
    {REST,     2, 0, 0, 1},
    {NOTE_AS6,  2, 0, 0, 1},
    {REST,     2, 0, 0, 1},
    {NOTE_B6,  2, 0, 0, 1},
    {REST,     1, 0, 0, 1},
    {REST,     2, 0, 0, 1},

    {NOTE_DS6,  2, 0, 0, 1},
    {REST,     2, 0, 0, 1},
    {NOTE_AS6,  2, 0, 0, 1},
    {REST,     2, 0, 0, 1},
    {NOTE_B6,  2, 0, 0, 1},
    {REST,     1, 0, 0, 1},
    {REST,     2, 0, 0, 1},

    {NOTE_CS6, 8, 1, 0, 1},
    {NOTE_DS6, 8, 1, 0, 1},
    {NOTE_CS6, -8, 1, 0, 1},
    {NOTE_B5,  4, 0, 0, 1},
    {NOTE_FS6, 1, 0, 0, 1},
    {REST,     1, 0, 0, 1},
};

byte eye_open[8] = {
  B00000,
  B01110,
  B01110,
  B01110,
  B01110,
  B01000,
  B01110,
  B00000,
};

byte eye_closed[8] = {
  B00000,
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
};

byte eye_happy[8] = {
  B00000,
  B00000,
  B01110,
  B10001,
  B10001,
  B10001,
  B10001,
  B00000,
};

// Calcula a quantidade de movementos da melodia
int notes = sizeof(melody)/sizeof(melody[0]);
int wholenote = (60000 * 4) / TEMPO;
int divider = 0, note_duration = 0;

// Inicializa display e servo
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

void animate_mouth(int vocal, int mouth_movement) {
    if (vocal == 1) {
        if (mouth_movement == 0) {
            lcd.clear();
            lcd.setCursor(5, 0);
            lcd.write(byte(0));
            lcd.setCursor(10, 0);
            lcd.write(byte(0));
            lcd.setCursor(5,1);
            lcd.print("-----");
        } else if (mouth_movement == 1) {
            lcd.clear();
            lcd.setCursor(5, 0);
            lcd.write(byte(1));
            lcd.setCursor(10, 0);
            lcd.write(byte(1));
            lcd.setCursor(5,1);
            lcd.print("  o");
        } else if (mouth_movement == 2) {
            lcd.clear();
            lcd.setCursor(5, 0);
            lcd.write(byte(1));
            lcd.setCursor(10, 0);
            lcd.write(byte(1));
            lcd.setCursor(5,1);
            lcd.print("  O");
        }
    }
}

void play_expression(int expression) {
    if (expression == 0) {
        servo.write(90);
    } else if (expression == 1) {
        servo.write(80);
    } else if (expression == 2) {
        servo.write(100);
    }
}

void setup() {
    servo.attach(3);
    servo.write(90);
    Wire.begin();
    lcd.init();
    lcd.setBacklight(HIGH);
    lcd.createChar(0, eye_open);
    lcd.createChar(1, eye_closed);
    lcd.createChar(2, eye_happy);

    lcd.setCursor(5, 0);
    lcd.write(byte(0));
    lcd.setCursor(10, 0);
    lcd.write(byte(0));
    lcd.setCursor(5,1);
    lcd.print("-----");

    delay(1000);

    // Canta a música
    for (int i=0; i<=notes; i++) {
        // Armazena o movimento atual em uma variável
        Movement movement = melody[i];
        divider = movement.duration;

        // Anima a boca do personagem
        animate_mouth(movement.vocal, movement.mouth_movement);
        // Reproduz as expressões corporais do personagem
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
}


void loop() {
}
