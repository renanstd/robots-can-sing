#include <Wire.h>
#include<LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

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

void setup() {
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

  delay(3000);
  
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.write(byte(2));
  lcd.setCursor(10, 0);
  lcd.write(byte(2));
  lcd.setCursor(5,1);
  lcd.print("  w");
}

void loop() {
}
