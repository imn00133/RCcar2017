// SW_pin connect to digital pin, X & Y pin connected analog pin
// A0=14, A1=15 ...
const int SW_pin = 14;
const int X_pin = 15;
const int Y_pin = 16;

void setup() {
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  Serial.begin(9600);
}

void loop() {
	int x = analogRead(X_pin);
	int y = analogRead(Y_pin);
	int SW = digitalRead(SW_pin);
	Serial.print("\nX_axis: ");
	Serial.print(x);
	Serial.print("\nY_axis: ");
	Serial.print(y);
	Serial.print("\nSW_pin: ");
	Serial.print(SW);
	delay(500);
}

// 아날로그 디지털 핀 사용하기
//http://studymake.blogspot.kr/2015/05/blog-post_58.html
