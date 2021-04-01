#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

Adafruit_SSD1306 display = Adafruit_SSD1306();
Servo servo;

void setup(){
  servo.attach(3);
  servo.write(90);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.clearDisplay();
}

void loop() {
  servo.write(80);
  
  display.clearDisplay();
  display.fillRect(30, 8, 10, 20, WHITE);
  display.fillRect(90, 8, 10, 20, WHITE);
  display.fillCircle(65, 25, 1, WHITE);
  display.display();
  delay(2500);
  
  display.clearDisplay();
  display.fillRect(30, 12, 10, 2, WHITE);
  display.fillRect(90, 12, 10, 2, WHITE);
  display.fillCircle(65, 25, 1, WHITE);
  display.display();
  delay(100);

  display.clearDisplay();
  display.fillRect(30, 8, 10, 20, WHITE);
  display.fillRect(90, 8, 10, 20, WHITE);
  display.fillCircle(65, 25, 1, WHITE);
  display.display();
  delay(2500);

  servo.write(100);
  display.clearDisplay();
  display.fillRect(30, 12, 10, 2, WHITE);
  display.fillRect(90, 12, 10, 2, WHITE);
  display.fillCircle(65, 25, 4, WHITE);
  display.display();
  
  for (int i=3136; i>2093; i--) {
    tone(11, i);
    delay(0.3);
  }
  for (int i=2093; i<3136; i++) {
    tone(11, i);
    delay(0.3);
  }

  noTone(11);
  delay(300); 
}
