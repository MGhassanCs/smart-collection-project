#include <ESP8266WiFi.h>
#include <Firebase_ESP_Client.h>
#include <addons/TokenHelper.h>
#include <addons/RTDBHelper.h>
#include <NewPing.h>

#define WIFI_SSID "Dining Hall - WiFi"
#define WIFI_PASSWORD ""
#define API_KEY "AIzaSyBtvj6QkvbdP0BrQKT80D1CssG22YMvQMY"
#define DATABASE_URL "https://junior-817bf-default-rtdb.asia-southeast1.firebasedatabase.app"
#define DATABASE_SECRETS_TOKEN "KOyORgwjYfxNwdzMeecBcYBentV5KaE6PZK2T3w1"
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long previous_millis = 0;
unsigned long update_interval = 5;

NewPing distance_sensor(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup()
{
  Serial.begin(115200);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  config.api_key = API_KEY;

  config.database_url = DATABASE_URL;
  config.signer.tokens.legacy_token = DATABASE_SECRETS_TOKEN;

  fbdo.setBSSLBufferSize(2048, 2048);
  fbdo.setResponseSize(2048);

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);

  Firebase.setDoubleDigits(5);

  config.timeout.serverResponse = 10 * 1000;
}


void loop()
{
  if (Firebase.ready() && (millis() - previous_millis > update_interval || previous_millis == 0))
  {
    int distance = distance_sensor.ping_cm()
    previous_millis = millis();
    Serial.printf("Set state... %s\n", Firebase.RTDB.setInt(&fbdo, F("/1/state"), distance) ? "ok" : fbdo.errorReason().c_str());
  }
}