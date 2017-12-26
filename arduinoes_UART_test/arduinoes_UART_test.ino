#include <SoftwareSerial.h>

int arduinoTX = 14;
int arduinoRX = 15;
SoftwareSerial arduinoSerial(arduinoTX, arduinoRX);
char user_input;

void setup()
{
  Serial.begin(9600);
  arduinoSerial.begin(9600);
}

void loop()
{
  if(Serial.available())
  {
    user_input=Serial.read();
    Serial.write(user_input);
    arduinoSerial.write(user_input);
  }
}
