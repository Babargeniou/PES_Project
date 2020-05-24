
#include <ArduinoBLE.h>
#include <Arduino_HTS221.h>
//16 bit UUID format
BLEService Environmental_Sensing("181A");  
BLEIntCharacteristic Temp_char("2A6E",  BLERead | BLENotify); 
BLEUnsignedIntCharacteristic Humid_char("2A6F", BLERead | BLENotify);

void setup() {
  Serial.begin(9600);    // Initialize serial communication
  while (!Serial);

  if (!HTS.begin()) {  // Initialize HTS22 sensor
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }

 // pinMode(LED_BUILTIN, OUTPUT); // Initialize the built-in LED pin

  if (!BLE.begin()) {   // Initialize BLE
    Serial.println("starting BLE failed!");
    while (1);
  }

  BLE.setLocalName("Arduino_NANO");  
  BLE.setAdvertisedService(Environmental_Sensing); 
  Environmental_Sensing.addCharacteristic(Temp_char); 
  Environmental_Sensing.addCharacteristic(Humid_char); 
  BLE.addService(Environmental_Sensing); 
  Temp_char.setValue(0); 
  Humid_char.setValue(0); 

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
    //digitalWrite(LED_BUILTIN, HIGH); //Indicate the connection when LED is ON 

    while (central.connected()) {
      long curr_Millis = millis();
      if (curr_Millis - prev_Millis >= Frequency_update) {
        prev_Millis = curr_Millis;
        updateReadings();
      }
    }
    //digitalWrite(LED_BUILTIN, LOW); //Indicate the connection failed when LED is OFF 
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
