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

// Test display with NAN inputs:
void loop() {
  float h = NAN;
  float t = NAN;

  if (isnan(h) || isnan(t)) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Sensor Err");
    display.display();
    delay(1500);
    return;
  }
}

// Test each plant type displays:
void loop() {
  for (int i = 0; i < 5; i++) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println(names[i]);

    display.setTextSize(1);
    display.println("Temp: 22 C");
    display.println("Humidity: 55 %");
    display.println("OK");

    display.display();
    delay(1500);
  }
}

// Test screen displays error when given bad inputs for the given plant:
void loop() {
  currentPlant = VEG;  // test specific plant

  float t = 100;  // far above any range
  float h = 0;    // far below any range

  bool alert = (
    t < ranges[currentPlant].tMin || t > ranges[currentPlant].tMax ||
    h < ranges[currentPlant].hMin || h > ranges[currentPlant].hMax
  );

  digitalWrite(ALERT_LED, alert ? HIGH : LOW);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.println(names[currentPlant]);

  display.setTextSize(1);
  display.print("Temp: "); display.println(t);
  display.print("Humidity: "); display.println(h);
  display.println(alert ? "ALERT! Out of range" : "OK");

  display.display();

  delay(2000);
}
