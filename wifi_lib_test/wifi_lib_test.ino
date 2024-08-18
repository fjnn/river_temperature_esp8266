// https://www.dofbot.com/post/esp8266-web-server-based-lm35-temperature-data-logger

// libraries for WIFI
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#include <SPI.h>

// libraries for DS18B20 temperature sensor
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2 // GPIO2 but D4. Weird...
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

// Replace with your network credentials
// const char* ssid = "PGV13";  // your SSID
// const char* password = "Prestegardsvegen13WIFI!";  // Your Wifi password
const char* ssid = "Galaxy Note10 Lite63a5";  // your SSID
const char* password = "msqa3560";  // Your Wifi password


// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

float temperatureC;

String getDStempC() {
   Serial.print("Temperature is : " );                       
   Serial.println(temperatureC);;
   return String(temperatureC); 
}


void setup () {
  sensors.begin(); // start DS18B20

  // Serial port for debugging purposes
  Serial.begin (9600);
  if (! SPIFFS.begin ()) {
    Serial.println ("An Error has occurred while mounting SPIFFS");
  return;
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.println("Connecting to WiFi..");
  }

  // Print connection information
  Serial.print("\nConnected to: ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");

  // Print ESP32 Local IP Address
  Serial.println(WiFi.localIP());

 // Route for web page
  server.on ("/", HTTP_GET, [] (AsyncWebServerRequest * request) {
    request-> send (SPIFFS, "/index.html");
  });

  server.on ("/DStempC", HTTP_GET, [] (AsyncWebServerRequest * request) {
    request-> send_P (200, "text / plain", getDStempC(). c_str ());
  });

  // start server
  server.begin ();

}


void loop() {
  sensors.requestTemperatures();
  temperatureC = sensors.getTempCByIndex(0);
  delay(1000);
}
