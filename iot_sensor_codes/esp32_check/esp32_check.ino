#define LED_PIN 2

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);

  Serial.print("Testing ESP32...");
  Serial.println("Serial communication is working");
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  Serial.print("LED ON\n");
  delay(1000);

  digitalWrite(LED_PIN, LOW);
  Serial.print("LED OFF\n");
  Serial.print("ESP32 is working 😝!\n");
  delay(1000);
}