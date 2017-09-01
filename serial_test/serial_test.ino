char user_input;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 if (Serial.available())
 {
  user_input=Serial.read();
  Serial.write(user_input);
 }
}
