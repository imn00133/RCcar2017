#include <SoftwareSerial.h>

//모터A in & 속도
int InA1 = 7;
int InA2 = 8;
int InAV = 6;

//모터B in & 속도
int InB1 = 9;
int InB2 = 10;
int InBV = 11;

//Stepmotor
//768번이 360도, 48step, 기어비 1:16
//declare variables for the motor pins
int motorPin1 = 2;    // Blue   - 28BYJ48 pin 1
int motorPin2 = 3;    // Pink   - 28BYJ48 pin 2
int motorPin3 = 4;    // Yellow - 28BYJ48 pin 3
int motorPin4 = 5;    // Orange - 28BYJ48 pin 4
                        // Red    - 28BYJ48 pin 5 (VCC)                     

int motorSpeed = 1200;  //variable to set stepper speed
int count = 0;          // count of steps made
int countsperrev = 512; // number of steps per full revolution
int lookup[8] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001};

//bluetooth
int blueTx = 12;
int blueRx = 13;
SoftwareSerial bluetoothSerial(blueTx, blueRx);

int carSpeed=127;
char user_input;

void setup() {
  //declare the motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
}

void loop() {
  user_input="";
  count=0;
  if (Serial.available())
  {
    user_input=Serial.read();
  }
  if (bluetoothSerial.available())
  {
    user_input = (char)bluetoothSerial.read();
  }
  if (user_input=='w')
  {
    testPrint();
    bothMotorStart();
  }
  if (user_input=='s')
  {
    testPrint();
    bothMotorReverse();
  }
  if (user_input=='a')
  {
    testPrint();
    while(count<1024){
      if(count < countsperrev )
        clockwise();
      else if (count == countsperrev * 2)
       count = 0;
     else
       anticlockwise();
     count++;
  }
  }
  if (user_input=='i')
  {
    testPrint();
    stopAllMotor();
  }
}
void testPrint()
{
  Serial.write(user_input);
  bluetoothSerial.write(user_input);
}
void bothMotorStart()
{
    digitalWrite(InA1,HIGH);
    digitalWrite(InA2,LOW);
    digitalWrite(InB1,HIGH);
    digitalWrite(InB2,LOW);
    analogWrite(InAV, carSpeed);
    analogWrite(InBV, carSpeed);
}

//모터A, B 역회전
void bothMotorReverse()
{
    digitalWrite(InA1,LOW);
    digitalWrite(InA2,HIGH);
    digitalWrite(InB1,LOW);
    digitalWrite(InB2,HIGH);
}
 
//모터A,B Stop
void stopAllMotor()
{
    digitalWrite(InA1,LOW);
    digitalWrite(InA2,LOW);
    digitalWrite(InB1,LOW);
    digitalWrite(InB2,LOW);
    analogWrite(InAV, carSpeed);
    analogWrite(InBV, carSpeed);
}
 
//모터A 역회전, 모터B 정회전
void turnLeft()
{
    digitalWrite(InA1,LOW);
    digitalWrite(InA2,HIGH);
    digitalWrite(InB1,HIGH);
    digitalWrite(InB2,LOW);
    analogWrite(InAV, carSpeed);
    analogWrite(InBV, carSpeed);
}
 
//모터A 정회전, 모터B 역회전
void turnRight()
{
    digitalWrite(InA1,HIGH);
    digitalWrite(InA2,LOW);
    digitalWrite(InB1,LOW);
    digitalWrite(InB2,HIGH);
    analogWrite(InAV, carSpeed);
    analogWrite(InBV, carSpeed);
}
 
//모터A 정회전, 모터B Stop
void motorA_Rotation()
{
    digitalWrite(InA1,HIGH);
    digitalWrite(InA2,LOW);
    digitalWrite(InB1,LOW);
    digitalWrite(InB2,LOW);
    analogWrite(InAV, carSpeed);
    analogWrite(InBV, carSpeed);
}
 
//모터A Stop, 모터B 정회전
void motorB_Rotation()
{
    digitalWrite(InA1,LOW);
    digitalWrite(InA2,LOW);
    digitalWrite(InB1,HIGH);
    digitalWrite(InB2,LOW);
    analogWrite(InAV, carSpeed);
    analogWrite(InBV, carSpeed);
}
 
//모터A 역회전, 모터B Stop
void motorA_Reverse()
{
    digitalWrite(InA1,LOW);
    digitalWrite(InA2,HIGH);
    digitalWrite(InB1,LOW);
    digitalWrite(InB2,LOW);
}
 
//모터A Stop, 모터B 역회전
void motorB_Reverse()
{
    digitalWrite(InA1,LOW);
    digitalWrite(InA2,LOW);
    digitalWrite(InB1,LOW);
    digitalWrite(InB2,HIGH);
    analogWrite(InAV, carSpeed);
    analogWrite(InBV, carSpeed);    
}
void anticlockwise()
{
  for(int i = 0; i < 8; i++)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}
 
void clockwise()
{
  for(int i = 7; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
}
 
void setOutput(int out)
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}
