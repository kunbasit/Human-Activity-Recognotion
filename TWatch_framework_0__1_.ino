#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <LIS3DHTR.h>
#include <TFT_eSPI.h>

#define WIFI_SSID "your_wifi_ssid"
#define WIFI_PASSWORD "your_wifi_password"
#define SERVER_URL "http://your_server_url:5000/data"

LIS3DHTR<TwoWire> imu(Wire);
TFT_eSPI tft = TFT_eSPI();

void setup() {
  Serial.begin(115200);
  Wire.begin();
  imu.begin(Wire);

  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextSize(2);
  tft.setCursor(0, 0);
  tft.setTextColor(TFT_WHITE);
  tft.println("Accelerometer Data");
  tft.println();
  tft.println("Connecting to WiFi...");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    tft.print(".");
  }
  tft.println();
  tft.println("WiFi connected!");
}

void loop() {
  float x = imu.readAccelerationX();
  float y = imu.readAccelerationY();
  float z = imu.readAccelerationZ();

  StaticJsonDocument<200> doc;
  doc["x"] = x;
  doc["y"] = y;
  doc["z"] = z;

  String body;
  serializeJson(doc, body);

  HTTPClient http;
  http.begin(SERVER_URL);
  http.addHeader("Content-Type", "application/json");
  int httpResponseCode = http.POST(body);
  if (httpResponseCode > 0) {
    tft.println("Data sent successfully!");
  } else {
    tft.println("Error sending data.");
  }
  http.end();

  delay(1000);
}

  