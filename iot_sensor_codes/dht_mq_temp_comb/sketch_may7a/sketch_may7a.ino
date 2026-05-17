// ---------------- LIBRARIES ----------------
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ---------------- DHT11 ----------------
#define DHTPIN 4
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// ---------------- MQ2 ----------------
#define MQ2PIN 34

// ---------------- DS18B20 ----------------
#define ONE_WIRE_BUS 5

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

// ---------------- SETUP ----------------
void setup() {

  Serial.begin(115200);

  Serial.println("==================================");
  Serial.println(" ESP32 MULTI SENSOR TEST ");
  Serial.println("==================================");

  // Start DHT11
  dht.begin();

  // Start DS18B20
  sensors.begin();
}

// ---------------- LOOP ----------------
void loop() {

  Serial.println("\n========== SENSOR DATA ==========");

  // ======================================
  // DHT11 SENSOR
  // ======================================

  float humidity = dht.readHumidity();
  float airTemp = dht.readTemperature();

  Serial.println("\n[DHT11 SENSOR]");

  if (isnan(humidity) || isnan(airTemp)) {
    Serial.println("DHT11 Reading Failed!");
  } else {

    Serial.print("Air Temperature: ");
    Serial.print(airTemp);
    Serial.println(" °C");

    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }

  // ======================================
  // MQ2 GAS SENSOR
  // ======================================

  int gasValue = analogRead(MQ2PIN);

  Serial.println("\n[MQ2 GAS SENSOR]");

  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  if (gasValue > 1500) {
    Serial.println("WARNING: Gas Detected!");
  } else {
    Serial.println("Air Quality Normal");
  }

  // ======================================
  // DS18B20 SENSOR
  // ======================================

  sensors.requestTemperatures();

  float waterTemp = sensors.getTempCByIndex(0);

  Serial.println("\n[DS18B20 WATER TEMPERATURE]");

  Serial.print("Water Temperature: ");
  Serial.print(waterTemp);
  Serial.println(" °C");

  Serial.println("\n==================================");

  delay(3000);
}