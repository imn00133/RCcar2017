#include <SoftwareSerial.h> //시리얼통신 라이브러리 호출
 
int blueTx=12;   //Tx (보내는핀 설정)at
int blueRx=13;   //Rx (받는핀 설정)
SoftwareSerial mySerial(blueTx, blueRx);  //시리얼 통신을 위한 객체선언
 
void setup() 
{
  Serial.begin(9600);   //시리얼모니터
  mySerial.begin(9600); //블루투스 시리얼
}
void loop()
{
  if (mySerial.available()) {       
    Serial.write(mySerial.read());  //블루투스측 내용을 시리얼모니터에 출력
  }
  if (Serial.available()) {         
    mySerial.write(Serial.read());  //시리얼 모니터 내용을 블루추스 측에 WRITE
  }
}
//https://m.blog.naver.com/PostView.nhn?blogId=makist2015&logNo=220408135622&proxyReferer=https%3A%2F%2Fwww.google.com%2F
