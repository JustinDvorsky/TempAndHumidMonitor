#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT11


DHT dht(DHTPIN, DHTTYPE);


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64


Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


void setup() {
 Serial.begin(9600);
 // Start the sensor, clear the display, and check for errors


 dht.begin();
 if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
   Serial.println("SSD1306 failed");
   while (true);
 }


 oled.clearDisplay();
 oled.display();
 Serial.println("Plant Temperature and Humidity Sensor\n");
}


void loop() {
 // Read the temp and humidity from the dht11 sensor, then convert it to Fahrenheit
 float humidity = dht.readHumidity();
 float tempC = dht.readTemperature();
 float tempF = tempC * 9.0 / 5.0 + 32.0;


 // Serial output the humidity levels and the temperature
 Serial.print("Humidity = ");
 Serial.print(humidity);
 Serial.print("%  ");


 Serial.print("Temperature = ");
 Serial.print(tempF);
 Serial.println(" F");


 // OLED Output of the temp and the humidity levels
 oled.clearDisplay();


 oled.setTextSize(1);
 oled.setTextColor(WHITE);
 oled.setCursor(0, 10);
 oled.println("Temp(F): ");


 oled.setTextSize(2);
 oled.setCursor(50, 20);
 oled.println(tempF);


 oled.setTextSize(1);
 oled.setCursor(0, 40);
 oled.println("Humidity(%): ");


 oled.setTextSize(2);
 oled.setCursor(50, 50);
 oled.println(humidity);


 oled.display();
 delay(2000);
}