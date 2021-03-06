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


void setup() {
  Serial.begin(9600);   /* opens serial port, sets data rate to 9600 bps */
  while (!Serial);


  //Initialize Temperature and Humidity sensor. 
  if (!HTS.begin()){ 
    Serial.println("Failed to initialize Temperature and Humidity Sensor!"); while (1);}
  

  
} // end setup



/* Initialize the variables  */


void loop() {

int limit = 100;
int len = 20; 
double avergTemper;
double sumTemper;
double temperArray[limit];
  

      Serial.print("Temperature =  ");
      for (int i = 1; i <= len ; i++) {
       // if (i < 10){
        temperArray[i] = HTS.readTemperature();
        Serial.println(i);
        Serial.println(temperArray[i]);
        //sumTemper =+ temperArray[i];
        //avergTemper = sumTemper/10;
      //  Serial.println(avergTemper);
        delay (1000);
       // }
        
     // sumTemper =+ HTS.readTemperature();
     // averTemper = sumTemper/len;
      }

      for (int i = 1; i<= len ; i++) {
        sumTemper += temperArray[i];
      //  Serial.println(sumTemper);
      }
      
        Serial.println("sumTemper");  
        Serial.println(sumTemper);   
        //avergTemper = sumTemper/len;
        Serial.println("Average Temperature");
        Serial.println(sumTemper/len);
        
     
     // Serial.println(" °C");
     // delay (1000);
      
     

    // wait 1 second to print again
     Serial.println("_____________________________________________________"); 
     delay(1000);
    
} // end loop
