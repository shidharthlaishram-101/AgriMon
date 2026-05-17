#define RELAY_PIN 26

void setup() {

  Serial.begin(115200);

  pinMode(RELAY_PIN, OUTPUT);

  // Relay OFF initially
  digitalWrite(RELAY_PIN, HIGH);

  Serial.println("Relay Test Started");
}

void loop() {

  // =========================
  // RELAY ON
  // =========================

  Serial.println("Relay ON");

  // Active LOW relay
  digitalWrite(RELAY_PIN, LOW);

  delay(3000);

  // =========================
  // RELAY OFF
  // =========================

  Serial.println("Relay OFF");

  digitalWrite(RELAY_PIN, HIGH);

  delay(3000);
}