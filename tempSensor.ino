/*Circuit:
 - Arduino Nano 33 BLE Board

 Group:3
 Babar Bashir
 Simi George 
 Deepa Gopi
 Neethu Josphe

*/

//#include <Arduino.h>
#include <Arduino_HTS221.h>

/* Initialize the variables  */

float temperature;
float humidity;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  while (!Serial);

  
  HTS.begin();   /* Initialize the humidity and temperature sensor.  */

  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

  else {
    Serial.println("Succesfully initialize humidity temperature sensor!");
    }

 
  
}

 

void loop() {
  // put your main code here, to run repeatedly:

  temperature = HTS.readTemperature();  /* Read the temperature sensor’s temperature value.   */
  humidity    = HTS.readHumidity();     /* Read the sensor’s measured relative humidity value */
  
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity = ");
  Serial.print(humidity);
  Serial.println(" %");

}
