#define TRIG_PIN 2
#define ECHO_PIN 3


void setup() { 
  Serial.begin(9600);
  pinMode(TRIG_PIN, OUTPUT); 
  pinMode(ECHO_PIN, INPUT);
}
 
void loop() 
{
  float distance = 0;  
 
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10); 
  digitalWrite(TRIG_PIN, LOW); 
  distance = pulseIn(ECHO_PIN, HIGH)/58.2; /* 센치미터(cm) */
  
  //시리얼모니터에 Echo가 HIGH인 시간 및 거리를 표시해준다.
  /*
  Serial.print("Duration:");
  Serial.print(duration);*/
  Serial.print("DIstance:");
  Serial.print(distance);
  Serial.println("cm\n");
  delay(500);

}

