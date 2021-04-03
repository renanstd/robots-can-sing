#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>


Adafruit_SSD1306 display = Adafruit_SSD1306();
Servo servo;


void setup(){
  servo.attach(3);
  Wire.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.clearDisplay();
}


void loop() {
  servo.write(90);

  display.clearDisplay();
  display.fillRect(30, 8, 10, 20, WHITE);
  display.fillRect(90, 8, 10, 20, WHITE);
  display.fillRect(34, 18, 6, 4, BLACK);
  display.fillRect(94, 18, 6, 4, BLACK);
  display.drawLine(60, 31, 70, 31, WHITE);
  display.display();
  delay(3000);

  display.clearDisplay();
  display.fillRect(30, 12, 10, 2, WHITE);
  display.fillRect(90, 12, 10, 2, WHITE);
  display.drawLine(60, 31, 70, 31, WHITE);
  display.display();
  delay(50);

  display.clearDisplay();
  display.fillRect(30, 8, 10, 20, WHITE);
  display.fillRect(90, 8, 10, 20, WHITE);
  display.fillRect(30, 18, 6, 4, BLACK);
  display.fillRect(90, 18, 6, 4, BLACK);
  display.drawLine(60, 31, 70, 31, WHITE);
  display.display();
  delay(2000);

  display.clearDisplay();
  display.fillRect(30, 8, 10, 20, WHITE);
  display.fillRect(90, 8, 10, 20, WHITE);
  display.fillRect(32, 18, 6, 4, BLACK);
  display.fillRect(92, 18, 6, 4, BLACK);
  display.drawLine(60, 31, 70, 31, WHITE);
  display.display();
  delay(800);

  display.clearDisplay();
  display.fillRect(30, 12, 10, 2, WHITE);
  display.fillRect(90, 12, 10, 2, WHITE);
  display.fillCircle(65, 25, 4, WHITE);
  display.display();
  delay(50);

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
  
  display.clearDisplay();
  display.fillRect(30, 12, 10, 2, WHITE);
  display.fillRect(90, 12, 10, 2, WHITE);
  display.fillCircle(65, 25, 6, WHITE);
  display.display();
  
  for (int i=2093; i<3136; i++) {
    tone(11, i);
    delay(0.3);
  }
  
  noTone(11);
  delay(300);
}
