int IN1=7;
int IN2=8;
int INEn=6;

void setup() {
  // put your setup code here, to run once:
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  motorStart();
}

void motorStart()
{
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  analogWrite(INEn, 222);
}

void stopMotor()
{
  analogWrite(INEn, 0);
}
void reverseMotor()
{
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  analogWrite(INEn, 222);
}
// http://deneb21.tistory.com/277
