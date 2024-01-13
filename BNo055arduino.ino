#include <WiFi.h>
#include <WiFiClient.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

#define WIFI_SSID "1BFB Hyperoptic 1Gb Fibre 2.4Ghz"
#define WIFI_PASSWORD "u7zK5AEzZPJZ"
#define TCP_PORT 8080 

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  Serial.begin(115200);
  delay(1000);

  
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WIFI_SSID);

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  if (!bno.begin()) {
    Serial.println("Could not find a valid BNO055 sensor, check wiring!");
    while (1);
  }
}

void loop() {
  sensors_event_t event;

 
  bno.getEvent(&event);

  // Send the sensor data over TCP
  WiFiClient client;
  if (!client.connect("Your Python listener IP address", TCP_PORT)) {
    Serial.println("Connection failed.");
    return;
  }

 /* Print the orientation values to the serial port */
  Serial.print("Orientation: ");
  Serial.print(event.orientation.x);
  Serial.print(", ");
  Serial.print(event.orientation.y);
  Serial.print(", ");
  Serial.println(event.orientation.z);
  client.print(",");
  client.print(event.gyro.x);
  client.print(",");
  client.print(event.gyro.y);
  client.print(",");
  client.print(event.gyro.z);
  client.print(",");
  client.print(event.acceleration.x);
  client.print(",");
  client.print(event.acceleration.y);
  client.print(",");
  client.print(event.acceleration.z);
  client.print("\n");

  client.stop();

  delay(100); // Change the delay time as needed
}


