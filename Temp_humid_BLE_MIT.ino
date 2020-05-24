/*Circuit:
Arduino Nano 33 BLE Board
Reading HTS221 temperature and humidity Sensor via Bluetooth using nRF Connect App 
 Group:3
 Babar Bashir
 Simi George 
 Deepa Gopi
 Neethu Joseph
*/
#include <ArduinoBLE.h>
#include <Arduino_HTS221.h>

BLEService App_Service("19B10000-E8F2-537E-4F6C-D104768A1214"); 
BLEByteCharacteristic App_char("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

void setup() {
  Serial.begin(9600);
  while (!Serial);
  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

  // begin initialization
  if (!BLE.begin()) {
    Serial.println("starting BLE failed!");
    while (1);
  }

  // set advertised local name and service UUID:
  BLE.setLocalName("Arduino_NANO");
  BLE.setAdvertisedService(App_Service);
  App_Service.addCharacteristic(App_char);
  BLE.addService(App_Service);
  App_char.writeValue(0);
  BLE.advertise();
  Serial.print("Peripheral device: ");
  Serial.println(BLE.address());
  Serial.println("Waiting for connections...");
}

void loop() {
  float temperature;
  float humidity;
  // listen for BLE peripherals to connect:
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
 
    while (central.connected()) {
      if (App_char.written()) {     
        byte Value = 1; 
        App_char.readValue(Value); 
 
        if (App_char.value()) {   // any value other than 0
          temperature = HTS.readTemperature();
          Serial.print("Temperature = ");
          Serial.print(temperature);
          Serial.println(" °C"); 
        } 
        else {                              // if 0 value
            humidity  = HTS.readHumidity();
            Serial.print("Humidity    = ");
            Serial.print(humidity);
            Serial.println(" %");
        }
      }
    }

    Serial.print(F("Disconnected from central: "));
    Serial.println(central.address());
  }
}
