#include <Servo.h> 
 
class Sweeper
{
  Servo servo;              // the servo
  int pos;              // current servo position 
  int increment;        // increment to move for each interval
  int  updateInterval;      // interval between updates
  unsigned long lastUpdate; // last update of position


public: 
  Sweeper(int interval)
  {
    updateInterval = interval;
    increment = 1;
  }
  
  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Detach()
  {
    servo.detach();
  }
  
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      Serial.println(pos);
      if ((pos >= 140) || (pos <= 80)) // end of sweep
      {
        // reverse direction
        increment = -increment;
      }
    }
  }
};
 
Sweeper sweeper1(80);
Sweeper sweeper2(80);
Sweeper sweeper3(80);
 
void setup() 
{ 
  Serial.begin(9600);
  sweeper1.Attach(9); //floorpin
  sweeper2.Attach(10); //pitdoor
  sweeper3.Attach(11); //hammer
} 
 
 void loop() 
{ 
 int randNumber = random(1,15); // generate random number between 1 & 15

    if(randNumber > 3 && < 7) 
    {
  sweeper1.Update(); //floorpin
    }
  if(randNumber >= 1 && <= 3)
  {
  sweeper3.Update(); //hammer
  delay(100);
  sweeper3.Update(); //hammer
  
  }

  if(digitalRead(2) == HIGH)
  {
     sweeper2.Update(); //pitdoor
     // call sound FX here
  }
} 