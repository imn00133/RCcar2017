
// SW_pin connect to digital pin, X & Y pin connected analog pin
// A0=14, A1=15 ...
const int SW_pin = 14;
const int X-pin = 15;
const int Y-pin = 16;

void setup() {
  pinMode(SW_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  Serial.print("X_axis: ");
  Serial.print(
}
// 아날로그 디지털 핀 사용하기
//http://studymake.blogspot.kr/2015/05/blog-post_58.html
