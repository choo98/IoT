#include <stdio.h>

//sensors and actuators here
int penmeter = A0;
int light_sensor = A1;
int blueLED = 2;
int redLED = 3;
bool manualInput;

//variables used to store values here
int tempSensorValue;
int lightSensorValue;
int temp;
unsigned int roomStatus = 0;

//variable to store readings and send to arduino
char buffer[30];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  tempSensorValue = analogRead(penmeter);
  lightSensorValue = analogRead(light_sensor);
  
  // convert potentiometer reading to sensor based on ranges
  if(tempSensorValue >= 0 && tempSensorValue <342)
  {
    temp = 32;  
  }
  else if (tempSensorValue > 341 && tempSensorValue <= 682)
  {
    temp = 35;
  }
  else
  {
    temp = 37;
  }
  
  //receive data from Edge_Device and turn on LED based on
  //commands received
if (Serial.available()>0)
{
  roomStatus = Serial.parseInt();
  if (roomStatus == 6)
  {
    manualInput = false;
  }    
  else if (roomStatus == 1 && manualInput == false)
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, LOW);
  }
  else if (roomStatus == 2 && manualInput == false)
  {
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, HIGH);
  }
  else if (roomStatus == 3 && manualInput == false)
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, HIGH);
  }
  else if (roomStatus == 4)
  {
    digitalWrite(redLED, HIGH);
    digitalWrite(blueLED, LOW);
    manualInput = true; 
  }
  else if (roomStatus == 5)
  {
    digitalWrite(redLED, LOW);
    digitalWrite(blueLED, HIGH);
    manualInput = true;
  }
}



  sprintf(buffer,"IOT Reading: %02d,%03d", temp, lightSensorValue);
  Serial.println(buffer);
  delay (2000);
  

}

   /*switch (roomStatus)
    {
      case 1:
        //TURN OFF AIRCOND ALMOST MORNING OR SOMETHING
        digitalWrite(redLED, HIGH);
        digitalWrite(blueLED, LOW);
        break;
     
      case 2:
        //TURN ON AIRCOND NIGHT TIME 
        digitalWrite(redLED, LOW);
        digitalWrite(blueLED, HIGH);
        break;
      case 3:
        //EMERGENCY TURN ON AIRCOND TOO HOT AND IT IS DAYTIME
        digitalWrite(redLED, HIGH);
        digitalWrite(blueLED, HIGH);
        break;
      case 4:
        //TURN OFF AIRCOND MANUALLY
        digitalWrite(redLED, HIGH);
        digitalWrite(blueLED, LOW);
        break;
      case 5:
        //TURN ON AIRCOND MANUALLY
        digitalWrite(redLED, LOW);
        digitalWrite(blueLED, HIGH);
        break;
      default:
        break;
    }*/ 
