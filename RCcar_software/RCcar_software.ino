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
//declare variables for the motor pins
int motorPin1 = 2;    // Blue   - 28BYJ48 pin 1
int motorPin2 = 3;    // Pink   - 28BYJ48 pin 2
int motorPin3 = 4;    // Yellow - 28BYJ48 pin 3
int motorPin4 = 5;    // Orange - 28BYJ48 pin 4
                      // Red    - 28BYJ48 pin 5 (VCC)                     

int motorSpeed = 1200;  //variable to set stepper speed, 숫자가 커지면 속도가 줄어든다.(microDlay사용)
int stepCount = 0;          // count of steps made, 몇 번 도는지 센다.
int countsperrev = 32; // number of steps per full revolution, 512가 1바퀴이다.
int lookup[9] = {B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001, B00000}; // 8step을 하나로 묶어놓았다. 마지막은 전류를 흐르지 않게 초기화

//bluetooth
int blueTx = 12;
int blueRx = 13;
SoftwareSerial bluetoothSerial(blueTx, blueRx);

int carSpeed;
char user_input;

void setup() {
  //declare the motor pins as outputs
  int carSpeed = 128;
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(motorPin3, OUTPUT);
  pinMode(motorPin4, OUTPUT);
  Serial.begin(9600);
  bluetoothSerial.begin(9600);
}

void loop() {
  user_input="";
  stepCount=0;
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
    while(stepCount < countsperrev)
    {
      clockwise();
      stepCount++;
    }
  }
  if (user_input=='d')
  {
    testPrint();
    while(stepCount < countsperrev)
    {
      anticlockwise();
      stepCount++;    
    }
  }
  if (user_input=='i')
  {
    testPrint();
    stopAllMotor();
  }
  if (user_input == 'o')
  {
	  speed_change();
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
  setOutput(8);
}
 
void clockwise()
{
  for(int i = 7; i >= 0; i--)
  {
    setOutput(i);
    delayMicroseconds(motorSpeed);
  }
  setOutput(8);
}
 
void setOutput(int out)
{
  digitalWrite(motorPin1, bitRead(lookup[out], 0));
  digitalWrite(motorPin2, bitRead(lookup[out], 1));
  digitalWrite(motorPin3, bitRead(lookup[out], 2));
  digitalWrite(motorPin4, bitRead(lookup[out], 3));
}

void speed_change() {
	if (carSpeed == 255) {
		carSpeed = 63;
	}
	else if (carSpeed < 64) {
		carSpeed = 127;
	}
	else
	{
		carSpeed = 255;
	}

}