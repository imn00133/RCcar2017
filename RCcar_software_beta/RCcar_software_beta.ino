#include <SoftwareSerial.h>

//모터 A in & 속도 핀
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
int lookup[9] = { B01000, B01100, B00100, B00110, B00010, B00011, B00001, B01001, B00000 }; // 8step을 하나로 묶어놓았다. 마지막은 전류를 흐르지 않게 초기화

//bluetooth
int blueTx = 12;
int blueRx = 13;
SoftwareSerial bluetoothSerial(blueTx, blueRx);

//arduino_UART
int arduinoTX = 14;
int arduinoRX = 15;
SoftwareSerial arduinoSerial(arduinoTX, arduinoRX);

//motor speed, maximum 255
int carSpeed;

//variable that user inputs the key
char userInput;

//do not move to front
char emergencyMode;

void setup() {
	//declare the motor pins as outputs
	carSpeed = 128;
	stepCount = 0;
	pinMode(motorPin1, OUTPUT);
	pinMode(motorPin2, OUTPUT);
	pinMode(motorPin3, OUTPUT);
	pinMode(motorPin4, OUTPUT);
	Serial.begin(9600);
	bluetoothSerial.begin(9600);
	arduinoSerial.begin(9600);
}

void loop() {
	userInput = ' ';
	emergencyMode = ' ';
	//all serial read
	if (Serial.available())
	{
		userInput = Serial.read();
	}
	if (bluetoothSerial.available())
	{
		userInput = (char)bluetoothSerial.read();
	}	
	if (Serial.available())
	{
		emergencyMode = (char)arduinoSerial.read();
	}

	//stepmotor zero-point control
	if (userInput == '0')
	{
		stepSetZero();
	}
	
	//motor operation
	if (userInput == '1' || userInput == '2' || userInput == '3')
	{
		if (emergencyMode != 's')
		{
			motor("front");
		}
	}
	else if (userInput == '7' || userInput == '8' || userInput == '9')
	{
		motor("back");
	}
	else
	{
		motor(" ");
	}

	//stepmotor operation
	if (userInput == '1' || userInput == '4' || userInput == '7')
	{
		stepmotor("clock");
	}
	else if (userInput == '3' || userInput == '6' || userInput == '9')
	{
		stepmotor("anticlock");
	}
	else
	{
		stepmotor(" ");
	}
}

void motor(String direction)
{
	if (direction == "front")
	{
		motorStart();
	}
	if (direction == "back")
	{
		motorReverse();
	}
	else
	{
		motorStop();
	}
}

void motorStart()
{
	digitalWrite(InA1, HIGH);
	digitalWrite(InA2, LOW);
	digitalWrite(InB1, HIGH);
	digitalWrite(InB2, LOW);
	analogWrite(InAV, carSpeed);
	analogWrite(InBV, carSpeed);
}

void motorReverse()
{
	digitalWrite(InA1, LOW);
	digitalWrite(InA2, HIGH);
	digitalWrite(InB1, LOW);
	digitalWrite(InB2, HIGH);
	analogWrite(InAV, carSpeed);
	analogWrite(InBV, carSpeed);
}

void motorStop()
{
	digitalWrite(InA1, LOW);
	digitalWrite(InA2, LOW);
	digitalWrite(InB1, LOW);
	digitalWrite(InB2, LOW);
	analogWrite(InAV, carSpeed);
	analogWrite(InBV, carSpeed);
}

void stepmotor(String direction)
{
	if (direction == "clock")
	{
		clockwise();
		stepCount++;
	}
	else if (direction == "anticlock")
	{
		antiClockwise();
		stepCount--;
	}
	else
	{
		if (stepCount > 0)
		{
			antiClockwise();
			stepCount--;
		}
		else if (stepCount < 0)
		{
			clockwise();
			stepCount++;
		}
	}
}

void clockwise()
{
	for (int i = 7; i >= 0; i--)
	{
		setOutput(i);
		delayMicroseconds(motorSpeed);
	}
	setOutput(8);
}

void antiClockwise()
{
	for (int i = 0; i < 8; i++)
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

int stepSetZero()
{
	if (Serial.available())
	{
		userInput = Serial.read();
	}
	if (bluetoothSerial.available())
	{
		userInput = (char)bluetoothSerial.read();
	}

	if (userInput == '0')
	{
		return 0;
	}
}