#include <WiFi.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"   // 👈 Add this
#include "addons/RTDBHelper.h"    // 👈 Add this

#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ---------------- WIFI ----------------
#define WIFI_SSID "Big W"
#define WIFI_PASSWORD "niqa1234"

// ---------------- FIREBASE ----------------
#define API_KEY "AIzaSyDlaty48o_XKGcGj5nNlvizStmFfzl4_cU"         // 👈 Fill this in from Firebase Console
#define DATABASE_URL "https://agrimon-iot-default-rtdb.asia-southeast1.firebasedatabase.app/"

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

// ---------------- FIREBASE OBJECTS ----------------
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

// ---------------- VARIABLES ----------------
bool smokeDetected = false;
bool signupOK = false;              // 👈 Track auth status

void setup() {
  Serial.begin(115200);

  dht.begin();
  sensors.begin();

  // Connect WiFi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi Connected! IP: " + WiFi.localIP().toString());

  // Firebase Config
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  // 👇 Anonymous sign-in (no email/password needed)
  if (Firebase.signUp(&config, &auth, "", "")) {
    Serial.println("Firebase Auth OK");
    signupOK = true;
  } else {
    Serial.println("Firebase Auth FAILED: " + String(config.signer.signupError.message.c_str()));
  }

  // 👇 Token status callback (required for mobizt library)
  config.token_status_callback = tokenStatusCallback;

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void loop() {

  // ---------------- SENSOR READINGS ----------------
  float humidity = dht.readHumidity();
  float airTemp  = dht.readTemperature();
  int   gasValue = analogRead(MQ2PIN);

  sensors.requestTemperatures();
  float waterTemp = sensors.getTempCByIndex(0);

  smokeDetected = (gasValue > 1500);

  // ---------------- PRINT DATA ----------------
  Serial.println("\n===== SENSOR DATA =====");
  Serial.print("Air Temp: ");    Serial.println(airTemp);
  Serial.print("Humidity: ");    Serial.println(humidity);
  Serial.print("Gas Value: ");   Serial.println(gasValue);
  Serial.print("Water Temp: ");  Serial.println(waterTemp);
  Serial.print("Smoke: ");       Serial.println(smokeDetected ? "YES" : "NO");

  // ---------------- SEND TO FIREBASE ----------------

  // 👇 Only send if Firebase is ready and auth succeeded
  if (Firebase.ready() && signupOK) {

    bool ok = true;

    if (!Firebase.RTDB.setFloat(&fbdo, "/sensors/airTemp", airTemp)) {
      Serial.println("airTemp FAILED: " + fbdo.errorReason());
      ok = false;
    }

    if (!Firebase.RTDB.setFloat(&fbdo, "/sensors/humidity", humidity)) {
      Serial.println("humidity FAILED: " + fbdo.errorReason());
      ok = false;
    }

    if (!Firebase.RTDB.setInt(&fbdo, "/sensors/gasLevel", gasValue)) {
      Serial.println("gasLevel FAILED: " + fbdo.errorReason());
      ok = false;
    }

    if (!Firebase.RTDB.setFloat(&fbdo, "/sensors/waterTemp", waterTemp)) {
      Serial.println("waterTemp FAILED: " + fbdo.errorReason());
      ok = false;
    }

    if (!Firebase.RTDB.setBool(&fbdo, "/sensors/smoke", smokeDetected)) {
      Serial.println("smoke FAILED: " + fbdo.errorReason());
      ok = false;
    }

    if (ok) {
      Serial.println("✅ All data sent to Firebase successfully!");
    }

  } else {
    Serial.println("⚠️ Firebase not ready — skipping send");
    Serial.println("   signupOK: " + String(signupOK));
    Serial.println("   Firebase.ready(): " + String(Firebase.ready()));
  }

  delay(5000);
}