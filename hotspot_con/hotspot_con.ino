#include <ESP8266WiFi.h>

void setup()
{
  Serial.begin(9600);
  Serial.println("here");
  pinMode(BUILTIN_LED, OUTPUT);


  WiFi.begin("Galaxy Note10 Lite63a5", "msqa3560");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  digitalWrite(BUILTIN_LED, HIGH);
  delay(100);
  digitalWrite(BUILTIN_LED, LOW);
  delay(100);


}