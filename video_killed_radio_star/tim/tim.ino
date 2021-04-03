#include "pitches.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include<LiquidCrystal_I2C.h>


const int TEMPO = 140;
const int BUZZER_PIN = 11;

struct Movement {
    int note;
    float duration;
    int mouth_movement;
    int expression;
    int vocal;
};

Movement melody[] = {
    // Intro
    // Tim
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_DS6, 2, 3, 1, 1},
    {REST,     4, 1, 1, 1},

    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_DS6, 2, 3, 1, 1},
    {REST,     4, 1, 1, 1},

    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_C6,  8, 2, 1, 1},
    {NOTE_C6,  8, 2, 1, 1},
    {NOTE_AS5, 8, 3, 1, 1},
    {NOTE_AS5, 8, 3, 1, 1},
    {NOTE_GS5, 8, 2, 1, 1},
    {NOTE_AS5, 8, 3, 1, 1},
    {NOTE_GS5, 8, 2, 1, 1},
    {NOTE_GS5, 8, 3, 1, 1},
    {NOTE_AS5, 8, 2, 1, 1},
    {NOTE_GS5, 2, 3, 1, 1},
    {REST,     8, 1, 1, 1},

    // Bridge
    // Timmy
    {NOTE_GS7, 4, 2, 2, 2},
    {NOTE_CS8, 8, 3, 1, 2},
    {NOTE_AS7, 2, 2, 3, 2},
    {REST,     8, 1, 1, 1},

    // Tim
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_F6,  4, 3, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {REST,     8, 1, 1, 1},

    // Timmy
    {NOTE_GS7, 4, 2, 2, 2},
    {NOTE_CS8, 8, 3, 1, 2},
    {NOTE_AS7, 2, 2, 3, 2},
    {REST,     8, 1, 1, 1},

    // Tim
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {NOTE_F6,  4, 3, 1, 1},
    {NOTE_DS6, 8, 3, 1, 1},
    {NOTE_CS6, 8, 2, 1, 1},
    {REST,     8, 1, 1, 1},

    // Chorus
    // Timmy
    {NOTE_GS7, 8, 2, 1, 2},
    {NOTE_GS7, 8, 2, 1, 2},
    {NOTE_GS7, 4, 2, 1, 2},
    {NOTE_GS7, 4, 2, 1, 2},
    {NOTE_GS7, 8, 2, 1, 2},
    {NOTE_GS7, 4, 2, 1, 2},
    {NOTE_AS7, 8, 2, 1, 2},
    {NOTE_FS7, 4, 2, 1, 2},
    {NOTE_FS7, 4, 2, 1, 2},
    {REST,     4, 1, 1, 2},

    {NOTE_GS7, 8, 2, 1, 2},
    {NOTE_GS7, 8, 2, 1, 2},
    {NOTE_GS7, 4, 2, 1, 2},
    {NOTE_GS7, 4, 2, 1, 2},
    {NOTE_GS7, 8, 2, 1, 2},
    {NOTE_GS7, 4, 2, 1, 2},
    {NOTE_AS7, 8, 2, 1, 2},
    {NOTE_FS7, 4, 2, 1, 2},
    {NOTE_FS7, 4, 2, 1, 2},
    {REST,     4, 1, 1, 2},
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
Adafruit_SSD1306 display = Adafruit_SSD1306();
LiquidCrystal_I2C lcd(0x27, 16, 2);
Servo servo;

void animate_mouth(int vocal, int mouth_movement) {
    if (vocal == 2) {
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
    } else if (vocal == 1) {
        if (mouth_movement == 2) {
            lcd.clear();
            lcd.setCursor(5, 0);
            lcd.write(byte(1));
            lcd.setCursor(10, 0);
            lcd.write(byte(1));
            lcd.setCursor(5,1);
            lcd.print("  o");
        } else if (mouth_movement == 3) {
            lcd.clear();
            lcd.setCursor(5, 0);
            lcd.write(byte(1));
            lcd.setCursor(10, 0);
            lcd.write(byte(1));
            lcd.setCursor(5,1);
            lcd.print("  O");
        } else if (mouth_movement == 1) {
            lcd.clear();
            lcd.setCursor(5, 0);
            lcd.write(byte(0));
            lcd.setCursor(10, 0);
            lcd.write(byte(0));
            lcd.setCursor(5,1);
            lcd.print("-----");
        }
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

    display.clearDisplay();
    display.fillRect(30, 8, 10, 20, WHITE);
    display.fillRect(90, 8, 10, 20, WHITE);
    display.fillRect(34, 18, 6, 4, BLACK);
    display.fillRect(94, 18, 6, 4, BLACK);
    display.drawLine(60, 31, 70, 31, WHITE);
    display.display();

    delay(1000);

    for (int i=0; i<=notes; i++) {
        // Armazena o movimento atual em uma variável
        Movement movement = melody[i];
        divider = movement.duration;

        // Anima a boca do personagem
        animate_mouth(movement.vocal, movement.mouth_movement);
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
