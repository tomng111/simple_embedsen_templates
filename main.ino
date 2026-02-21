// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 2
#define led 13
int sollwert = 30;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*
 * The setup function. We only start the sensors here
 */
void setup(void)
{
  // start serial port
  Serial.begin(9600);
  //Serial.println("Dallas Temperature IC Control Library Demo");

  // Start up the library
  sensors.begin();
  // LED
  pinMode(led, OUTPUT);
}

/*
 * Main function, get and show the temperature
 */
void loop(void)
{
  // Kommunikation-Received
  String datum ="";
  if(Serial.available() > 0){
    datum = Serial.readStringUntil('\n');
  }
  if(datum != ""){
    sollwert = datum.toFloat();
    datum = "";
  }
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  //Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  //Serial.println("DONE");
  
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
  float tempC = sensors.getTempCByIndex(0);
  if(tempC > sollwert){
    digitalWrite(led, HIGH);
    Serial.println("!"+String(tempC)+"@"+"EIN"+"#"+String(sollwert));
  }
  else {
    digitalWrite(led, LOW);
    Serial.println("!"+String(tempC)+"@"+"AUS"+"#"+String(sollwert));
  }
  delay(500);
}
