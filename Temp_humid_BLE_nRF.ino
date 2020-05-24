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
//16 bit UUID format
BLEService Environmental_Sensing("181A");  
BLEIntCharacteristic Temp_char("2A6E",  BLERead | BLENotify); 
BLEUnsignedIntCharacteristic Humid_char("2A6F", BLERead | BLENotify);
//128 bit UUID format
//BLEService App_Service("19B10000-E8F2-537E-4F6C-D104768A1214"); 
//BLEByteCharacteristic App_chara("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);


void setup() {
  Serial.begin(9600);    // Initialize serial communication
  while (!Serial);
  
  if (!HTS.begin()) {  // Initialize HTS22 sensor
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

  if (!BLE.begin()) {   // Initialize BLE
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Arduino_NANO");  
  BLE.setAdvertisedService(Environmental_Sensing);
  //BLE.setAdvertisedService(App_Service); 
  Environmental_Sensing.addCharacteristic(Temp_char); 
  Environmental_Sensing.addCharacteristic(Humid_char); 
  //App_Service.addCharacteristic(App_chara);
  BLE.addService(Environmental_Sensing); 
  //BLE.addService(App_Service);
  Temp_char.setValue(0); 
  Humid_char.setValue(0);
  //App_chara.writeValue(0); 

  BLE.advertise();  // Start advertising
  Serial.print("Peripheral device MAC: ");
  Serial.println(BLE.address());
  Serial.println("Waiting for connections...");
}

void loop() {
  BLEDevice central = BLE.central();  
  const int Frequency_update = 2000; 
  long prev_Millis = 0;  
  if (central) {   // If central is connected to peripheral
    Serial.print("Connected to central MAC: ");
    Serial.println(central.address());  // Central BLE address

    while (central.connected()) {
      long curr_Millis = millis();
      if (curr_Millis - prev_Millis >= Frequency_update) {
        prev_Millis = curr_Millis;
        updateReadings();
      }
//      if(App_chara.written()) {
//        float Temp_value = HTS.readTemperature();
//        Serial.print("Temperature = ");
//        Serial.print(Temp_value);
//        Serial.println(" °C");
//      }
//      if(!App_chara.written()) {
//        float Humid_value = HTS.readHumidity();
//        Serial.print("Humidity = ");
//        Serial.print(Humid_value);
//        Serial.println(" %");
//      }
    } 
    Serial.print("Disconnected from central MAC: ");
    Serial.println(central.address());
  }
}

float getTemperature(float calibration) {
  float temperature_read=HTS.readTemperature();
  return ((temperature_read * 100 )+ (calibration * 100));
}

float getHumidity() {
  float humidity_read=HTS.readHumidity();
  return (humidity_read * 100);
}

void updateReadings() {
   float CALIBRATION_FACTOR = -2.0; 
   float prev_Temp = 0;
   float prev_Humid= 0;
   float temperature = getTemperature(CALIBRATION_FACTOR);
   float humidity = getHumidity();
   if (temperature != prev_Temp) {  
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Temp_char.writeValue(temperature); 
    prev_Temp = temperature;          
   }
   
   if (humidity != prev_Humid) {
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
    Humid_char.writeValue(humidity);
    prev_Humid = humidity;
   }
}
