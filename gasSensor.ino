/*Circuit:
 - Arduino Nano 33 BLE Board

Reading HTS221 Sensor

 Group:3
 Babar Bashir
 Simi George 
 Deepa Gopi
 Neethu Joseph

*/

#include"Air_Quality.h"
#include"Arduino.h"

AirQuality airqualitysensor;
int current_quality =-1;
const int pin19 = A0;   // input pin

const int ledPin = 22;    // Red led
const int ledPin2 = 23;   // Green led
const int ledPin3 = 24;   // Blue led

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  airqualitysensor.init(A0);
  
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(24, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  current_quality=airqualitysensor.slope();
    if (current_quality >= 0)// if a valid data returned.
    {
        if (current_quality ==0){
           // Serial.println("High pollution! Force signal active");
            Serial.println("Red LED ON");
            digitalWrite(ledPin, LOW);            // Red
            digitalWrite(ledPin2, HIGH);    
            digitalWrite(ledPin3, HIGH);   
           
        }
            
        else if (current_quality == 1){
         // Serial.println("High pollution!");
            Serial.println("Blue LED ON");
            digitalWrite(ledPin, HIGH);          
            digitalWrite(ledPin2, HIGH);           
            digitalWrite(ledPin3, LOW);           // Blue
        
        }
            
        else if (current_quality == 2){
           //Serial.println("Low pollution!");
            Serial.println(" Green LED ON");
            digitalWrite(ledPin, HIGH);          
            digitalWrite(ledPin2, LOW);             // Green
            digitalWrite(ledPin3, HIGH);            
         }
            
        else if (current_quality == 3){
          //Serial.println("Air fresh");
            Serial.println("LED OFF");      
            digitalWrite(ledPin, HIGH);     
            digitalWrite(ledPin2, HIGH);    
            digitalWrite(ledPin3, HIGH);   
        }
     
    }


    //if(airqualitysensor.counter==122)//set 2 seconds as a detected duty
    if(airqualitysensor.counter==61)//set 2 seconds as a detected duty
    {
        airqualitysensor.last_val=airqualitysensor.first_val;
        airqualitysensor.first_val=analogRead(A0);
        airqualitysensor.counter=0;
        airqualitysensor.timer_index=1;
   
    }
    else
    {
        airqualitysensor.counter++;
    }

     
     delay(500);
     Serial.println("_____________________________________________________");

}
