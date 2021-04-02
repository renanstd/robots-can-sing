#include <Wire.h>
#include<LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);

byte eye_open[8] = {
  B00000,
  B11110,
  B11110,
  B11110,
  B11110,
  B11000,
  B11110,
  B00000,
};

void setup() {
  lcd.init();
  lcd.setBacklight(HIGH);

  lcd.createChar(0, eye_open);

  lcd.setCursor(5, 0);
  lcd.write(byte(0));
  lcd.setCursor(10, 0);
  lcd.write(byte(0));
  lcd.setCursor(5,1);
  lcd.print("-----");

}

void loop() {
}
