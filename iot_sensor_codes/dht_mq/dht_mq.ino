#include <DHT.h>

#define DHTPIN 4
#define DHTTYPE DHT11
#define MQ2PIN 34

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  delay(1000);

  dht.begin();
}

void loop() {
  int gasValue = analogRead(MQ2PIN);
  Serial.println("\n MQ2 Sensor 👇");
  Serial.print("Gas Level: ");
  Serial.println(gasValue);

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  Serial.println("\n DHT11 Sensor 👇");
  Serial.print("Temperature: ");
  Serial.print(temperature);

  Serial.print("\n Humidity: ");
  Serial.print(humidity);

  delay(2000);
}

