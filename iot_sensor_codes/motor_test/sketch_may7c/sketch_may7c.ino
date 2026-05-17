#define MOTOR_PIN 23

// Active LOW relay logic
#define RELAY_ON  HIGH
#define RELAY_OFF LOW

void setup() {
  Serial.begin(115200);

  pinMode(MOTOR_PIN, OUTPUT);

  // Keep motor OFF at startup
  digitalWrite(MOTOR_PIN, RELAY_OFF);

  Serial.println("Motor Test Started");
}

void loop() {

  // Turn Motor ON
  digitalWrite(MOTOR_PIN, RELAY_ON);
  Serial.println("Motor ON");
  delay(5000);

  // Turn Motor OFF
  digitalWrite(MOTOR_PIN, RELAY_OFF);
  Serial.println("Motor OFF");
  delay(5000);
}