#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
void setup() {
 Serial.begin(9600);
 if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
   Serial.println("OLED FAIL");
   while (true);
 }
 oled.clearDisplay();
 oled.setTextColor(WHITE);
 oled.setTextSize(2);
 oled.setCursor(0, 0);
 oled.println("OLED");
 oled.setTextSize(1);
 oled.setCursor(0, 30);
 oled.println("Display test");
 oled.display();
}
void loop() {}