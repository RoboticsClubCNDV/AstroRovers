/* including necessary libraries
SoftwareSerial.h for data receiving
Servo.h for the servomotor
*/
#include <SoftwareSerial.h>
#include <Servo.h>


// the pins for the motors
int MOTOR2_PIN1 = 3;
int MOTOR2_PIN2 = 5;
int MOTOR1_PIN1 = 6;
int MOTOR1_PIN2 = 9;


// the pins for metane and carbon monoxide sensors
int methanePin = A0;
int carbonPin = A1;


// variables used for the servomotor
Servo servo; // pin used for the servomotor
int pos; // the position of the servomotor


/* variable used to receive data
For direction: 
  W - forward
  S - backwards
  D - right
  A - left
For the servomotor:
  L - forward (in degrees)
  O - backwards
Sensors:
  M - methane
  C - carbon monoxide
  *others on the Raspberry Pi code*
*/
char data;

 
void setup() 
{
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  Serial.begin(9600);
}

void loop() 
{
  while(Serial.available()>0)
  {
    data=Serial.read();
    Serial.write(data);
    if(data=='W' || data=='w') 
    { 
        go(255,255);
    }
    if (data=='D' || data=='D')
    {
        go(-255,255);
    }
  
    if(data=='A' || data=='A')
    {
        go(255,-255);
    
    }
    if(data=='S' || data=='s')
    {
        go(-255,-255);
    }   
    if((data == 'L' || data=='l') && pos<=180)
     { 
      for(pos = 0; pos < 90; pos += 1)  
      {                                 
        servo.write(pos);              
        delay(15);                      
      }   
     }
    if((data == 'O' || data=='o') && pos>=0)
     {
       for(pos = 90; pos>=1; pos-=1)     
        {                                
          servo.write(pos);              
          delay(15);                       
         } 
     }
     if(data == 'Y' || data == 'y')
     {
       servo.detach();
     }
     if(data == 'U' || data =='u')
     {
       servo.attach(8);
     }
     if(data=='M' || data=='m')
     {
       Serial.print("ethane:");
       Serial.print(analogRead(methanePin));
       Serial.println(" mg/L");
     }
     if(data=='C' || data=='c')
     {
       Serial.print("arbon monoxide:");
       Serial.print(analogRead(carbonPin));
       Serial.println(" mg/L");
     }
  }
}

void go(int speedLeft, int speedRight)// function used for moving
{
  if (speedLeft > 0) 
  {
    analogWrite(MOTOR1_PIN1, speedLeft);
    analogWrite(MOTOR1_PIN2, 0);
  } 
  else 
  {
    analogWrite(MOTOR1_PIN1, 0);
    analogWrite(MOTOR1_PIN2, -speedLeft);
  }
 
  if (speedRight > 0) 
  {
    analogWrite(MOTOR2_PIN1, speedRight);
    analogWrite(MOTOR2_PIN2, 0);
  }
  else 
  {
    analogWrite(MOTOR2_PIN1, 0);
    analogWrite(MOTOR2_PIN2, -speedRight);
  }
}


