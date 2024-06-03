/* Arduino DS18B20 temp sensor tutorial
   More info: http://www.ardumotive.com/how-to-use-the-ds18b20-temperature-sensor-en.html
   Date: 19/6/2015 // www.ardumotive.com */


//Include libraries
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into pin 2 on the Arduino
#define ONE_WIRE_BUS 2 // GPIO2 but D4. Weird...
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void)
{
  Serial.begin(9600); //Begin serial communication
  Serial.println("Arduino Digital Temperature // Serial Monitor Version"); //Print a message
  sensors.begin();
}

void loop(void)
{ 
  sensors.requestTemperatures();
  float temperatureC = sensors.getTempCByIndex(0);
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print("Temperature in Celsius : ");
  Serial.print(temperatureC);
  Serial.print(" C");
  Serial.print("\tTemperature in Fahrenheit : ");
  Serial.print(temperatureF);
  Serial.println(" F");
  delay(1000);
}