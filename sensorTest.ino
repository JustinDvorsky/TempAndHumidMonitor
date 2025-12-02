#include <DHT.h>
#define DHTPIN 7
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);


void setup() {
 Serial.begin(9600);
 dht.begin();
 Serial.println("DHT11 Test...");
}


void loop() {
 float h = dht.readHumidity();
 float t = dht.readTemperature();
 float f = t * 9.0 / 5.0 + 32.0;


 Serial.print("Humidity: ");
 Serial.print(h);
 Serial.print("%  Temp: ");
 Serial.print(f);
 Serial.println(" F");


 delay(2000);
}