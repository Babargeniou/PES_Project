/*Circuit:
 - Arduino Nano 33 BLE Board

Reading HTS221 Sensor and Bluetooth

 Group:3
 Babar Bashir
 Simi George 
 Deepa Gopi
 Neethu Joseph

*/


#include <Arduino_HTS221.h> //Include library to read Temperature and Humidity
#include <ArduinoBLE.h>

//BLEUnsignedCharCharacteristic temperatureLevelChar("2101", BLERead | BLENotify);
//const int ledPin = 22;    // Red led
//const int ledPin2 = 23;   // Green led
//const int ledPin3 = 24;   // Blue led

void setup() {


  //pinMode(23, OUTPUT);
  //pinMode(24, OUTPUT);
  
  Serial.begin(9600);   /* opens serial port, sets data rate to 9600 bps */
  while (!Serial);


  //Initialize Temperature and Humidity sensor. 
  if (!HTS.begin()){ 
    Serial.println("Failed to initialize Temperature and Humidity Sensor!"); while (1);}
  

  //Initialization bluetooth module.
  if (!BLE.begin()){
    Serial.println("starting BLE failed!"); while (1);}
    

  BLE.setLocalName("ArduinoSensorMonitor");
  
  BLE.advertise();
  Serial.println("Bluetooth device active, waiting for connections...");


  
} // end setup



/* Initialize the variables  */


void loop() {

  // Check if a Device has been discovered
 // BLEDevice central = BLE.available();
  //float temperature = HTS.readTemperature();

BLEDevice central = BLE.central();

if (central) {
  
    Serial.print("Connected to central: ");
    Serial.println(central.address());
    digitalWrite(LED_BUILTIN, HIGH);
    
    while(central.connected()){
      Serial.print("Temperature =  ");
      Serial.println(HTS.readTemperature());
 // temperatureLevelChar.writeValue(tempVal);
      Serial.println(" °C");
      delay (1000);

     Serial.print("Humidity = ");
     Serial.print(HTS.readHumidity());
     Serial.println(" %");
     delay (1000);
    }
    
   }

  //Serial.print("Humidity = ");
  //Serial.print(humidity);
  //Serial.println(" %");
  //delay (1000);

   //wait 1 second to print again
 // Serial.println("_____________________________________________________"); 
  //delay(1000);
  //Serial.end();
 

// } // end while
//  } // end if
//else {
digitalWrite(LED_BUILTIN, LOW);
//digitalWrite(ledPin2, LOW);
Serial.print("Disconnected from central: ");
Serial.println(central.address());
delay(1000);
//}
} // end loop
