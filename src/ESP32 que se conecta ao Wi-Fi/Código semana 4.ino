#include <WiFi.h>

#define led_red 10
#define led_blue 12

const char* ssid = "ESP32-AP";
const char* password = "12345678";

void setup() {
  Serial.begin(115200);
  pinMode(led_red, OUTPUT);
  pinMode(led_blue, OUTPUT);

  WiFi.mode(WIFI_AP_STA);
  delay(100);
  WiFi.begin(ssid, password);

  digitalWrite(led_red, LOW);
  digitalWrite(led_blue, LOW);


  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(led_blue, HIGH);
  }
}

void loop() {
  while (WiFi.status() == WL_CONNECTED) {
    digitalWrite(led_red, !digitalRead(led_red));
    delay(600);
    digitalWrite(led_blue, LOW);
    Serial.println("O esp32 está conectado à internet!");
  }

  while (WiFi.status() != WL_CONNECTED) {
    digitalWrite(led_blue, !digitalRead(led_blue));
    delay(600);
    digitalWrite(led_red, LOW);
  
    Serial.println("O esp32 não está conectado à internet!");
    WiFi.begin(ssid, password);
    delay(100);
  }
}