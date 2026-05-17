#include <OneWire.h>
#include <DallasTemperature.h>

// ---------------- PIN ----------------
#define DS18B20_PIN 5   // GPIO5

// ---------------- SETUP SENSOR ----------------
OneWire oneWire(DS18B20_PIN);
DallasTemperature sensors(&oneWire);

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(115200);

  Serial.println("DS18B20 Temperature Sensor Test");

  sensors.begin();
}

// ---------------- LOOP ----------------
void loop() {

  // Request temperature reading
  sensors.requestTemperatures();

  // Get temperature in Celsius
  float temperatureC = sensors.getTempCByIndex(0);

  Serial.print("Temperature: ");
  Serial.print(temperatureC);
  Serial.println(" °C");

  delay(2000);
}