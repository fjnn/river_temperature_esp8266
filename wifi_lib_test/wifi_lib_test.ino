https://www.dofbot.com/post/esp8266-web-server-based-lm35-temperature-data-logger

#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>
#include <SPI.h>

// Replace with your network credentials
const char* ssid = "PGV13";  // your SSID
const char* password = "Prestegardsvegen13WIFI!";  // Your Wifi password

const int LM35 = A0;  
int input_val = 0;
float temp = 0;  

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String getDStempC() {
   input_val = analogRead(LM35);
   temp = (3300 * input_val ) / 1024; 
   Serial.print("Temperature is : " );                       
   Serial.println(temp);;
   return String(temp); 
}


void setup () {
  // Serial port for debugging purposes
  Serial.begin (115200);
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


void loop() {}
