#include <DHT.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// OLED Screen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// DHT11 Sensor
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Button
#define BTN_MODE 2

// LED
#define ALERT_LED 13

// For debounce
unsigned long lastDebounceTime = 0;
bool lastStableState = HIGH;
const unsigned long debounceDelay = 50;

// Plant types
enum PlantType {VEG, SUCC, FLOWER, FRUIT, FERN};
PlantType currentPlant = VEG;


struct PlantRange {
  float tMin, tMax;
  float hMin, hMax;
};

// These are the ranges for the plants minimum/maximum temp and humidity in this order: Veg, succ, flower, fruit, fern
PlantRange ranges[5] = {{18, 26, 40, 70}, {10, 32, 10, 40}, {15, 24, 30, 60}, {20, 28, 40, 80}, {16, 24, 50, 90}};

String names[5] = {"Vegetable", "Succulent", "Flower", "Fruit", "Fern"};


bool debounceButton() {
  static bool lastReading = HIGH;
  bool reading = digitalRead(BTN_MODE);

  // reset debounce timer when reading changes
  if (reading != lastReading) {
    lastDebounceTime = millis();
  }

  // if stable for long enough, accept the button press
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != lastStableState) {
      lastStableState = reading;

      // register only on press
      if (lastStableState == LOW) {
        lastReading = reading;
        return true;
      }
    }
  }

  lastReading = reading;
  return false;
}

void setup() {
  pinMode(BTN_MODE, INPUT_PULLUP);
  pinMode(ALERT_LED, OUTPUT);

  dht.begin();

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextColor(WHITE);
}

void loop() {

  // Button pressed, cycle to next plant
  if (debounceButton()) {
    currentPlant = (PlantType)((currentPlant + 1) % 5);
  }

  // read sensor
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("Sensor Err");
    display.display();
    return;
  }

  // Check alert range
  bool alert = (t < ranges[currentPlant].tMin || t > ranges[currentPlant].tMax || h < ranges[currentPlant].hMin || h > ranges[currentPlant].hMax);

  digitalWrite(ALERT_LED, alert ? HIGH : LOW);

  // Update OLED screen
  display.clearDisplay();
  display.setCursor(0, 0);

  display.setTextSize(2);
  display.println(names[currentPlant]);
  display.setTextSize(1);

  display.print("Temp: ");
  display.print(t);
  display.println(" C");

  display.print("Humidity: ");
  display.print(h);
  display.println(" %");

  display.println(alert ? "ALERT! Out of range" : "OK");

  display.display();

  delay(150);
}