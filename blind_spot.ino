#include <HCSR04.h>
int val=0;
UltraSonicDistanceSensor distanceSensor(13, 12);  // Initialize sensor that uses digital pins 13 for Trigger and 12 for Echo.

void Object_detection()
{
       if(val<=50)
       {
           digitalWrite(4, HIGH);
           delay(1000);
           digitalWrite(4, LOW);
           delay(1000);
       }
       else if(val>=51)
       {
         digitalWrite(4, LOW);
       }
}

void signal_function()
{
        if(digitalRead(5) == 1)
         {
           digitalWrite(6, HIGH);
         }
         else
         {
           digitalWrite(6, LOW);
         }
}

void buzzer_fuction()
{
    while((digitalRead(5) == 1) && (val<=50))
    {
      val=distanceSensor.measureDistanceCm();
      digitalWrite(4, HIGH);
      delay(200);
      digitalWrite(4, LOW);
      delay(200);
      digitalWrite(7, HIGH);
    }
  if((digitalRead(5) == 1) && (val>=51))
  {
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
  }
  if(digitalRead(5) == 0 && (val<=50))
  {
    digitalWrite(4, HIGH);
    digitalWrite(7, LOW);
  }
  if(digitalRead(5) == 0 && (val>=51))
  {
    digitalWrite(4, LOW);
    digitalWrite(7, LOW);
  }
}

void setup () 
{
    Serial.begin(9600);  //We initialize serial connection so that we could print values from sensor.
    pinMode(4, OUTPUT);
    pinMode(5, INPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
}

void loop () 
{
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
 val=distanceSensor.measureDistanceCm();
 Object_detection();
 signal_function();
 buzzer_fuction(); 
   
}
