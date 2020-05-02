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
//const int pin20 = A1;   // output pin
const int ledPin3 = 24;   // output pin

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);
  airqualitysensor.init(A0);

 // pinMode(D2,OUTPUT);
 pinMode(24, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  current_quality=airqualitysensor.slope();
    if (current_quality >= 0)// if a valid data returned.
    {
        if (current_quality ==0){
           // Serial.println("High pollution! Force signal active");
            Serial.println("LED ON");
            digitalWrite(ledPin3, LOW);
        }
            
        else if (current_quality == 1){
         // Serial.println("High pollution!");
            Serial.println("LED ON");
            digitalWrite(ledPin3, LOW);
        }
            
        else if (current_quality == 2){
           //Serial.println("Low pollution!");
            Serial.println("LED OFF");
            digitalWrite(ledPin3, HIGH);
        }
            
        else if (current_quality == 3){
          //Serial.println("Air fresh");
            Serial.println("LED OFF");
            digitalWrite(ledPin3, HIGH);
        }
     
    }

//ISR(TIMER2_OVF_vect)
//AttachInterrupt()
//{
    //if(airqualitysensor.counter==122)//set 2 seconds as a detected duty
    if(airqualitysensor.counter==61)//set 2 seconds as a detected duty
    {
        airqualitysensor.last_val=airqualitysensor.first_val;
        airqualitysensor.first_val=analogRead(A0);
        airqualitysensor.counter=0;
        airqualitysensor.timer_index=1;
       // PORTB=PORTB^0x20;
    }
    else
    {
        airqualitysensor.counter++;
    }
//}

     
     
     delay(100);

}
