// 본 프로젝트에서 사용하는 실드에서 제공하는 2개의 I2C핀 중 아무곳이나 연결 가능(병렬 출력 방식)

#include <Wire.h>  // I2C 통신을 위한 헤더파일 호출
#include <Adafruit_GFX.h>  // 그래픽 관련 기능을 제공하는 헤더파일 호출
#include <Adafruit_SSD1306.h>  // SSD1306 OLED 디스플레이를 제어하기 위한 헤더파일 호출

#define SCREEN_WIDTH 128  // OLED 디스플레이의 너비 (픽셀 단위)
#define SCREEN_HEIGHT 64  // OLED 디스플레이의 높이 (픽셀 단위)
#define OLED_RESET -1  // OLED 디스플레이의 리셋 핀 (-1은 리셋 핀 공유를 의미)
#define SCREEN_ADDRESS 0x3C  // I2C 주소 (128x64 OLED 디스플레이의 기본 주소는 0x3C)

// Adafruit_SSD1306 객체 생성: 디스플레이의 크기, I2C 통신을 위한 Wire 객체, 리셋 핀을 지정
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(9600);  // 시리얼 통신을 9600 baud rate로 설정

  // 디스플레이 초기화. 초기화 실패 시 에러 메시지 출력 후 무한 루프
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));  // 시리얼 모니터에 오류 메시지 출력
    for(;;);  // 오류 발생 시 프로그램 중단
  }

  // 디스플레이를 초기화하고 텍스트 출력
  display.clearDisplay();  // 버퍼를 초기화하여 화면을 지움
  display.setTextSize(2);  // 텍스트 크기를 2배로 설정
  display.setTextColor(SSD1306_WHITE);  // 텍스트 색상을 흰색으로 설정
  display.setCursor(0, 0);  // 커서를 (0,0) 위치로 설정하여 텍스트 시작 위치 지정
  display.println("Smart");  // 첫 번째 텍스트 라인 출력
  display.println("Vivarium");  // 두 번째 텍스트 라인 출력
  display.println("Test"); // 세 번째 텍스트 라인 출력
  display.print("by kimyw33");  // 네 번째(마지막) 텍스트 라인 출력
  display.display();  // 화면에 버퍼 내용을 출력
  delay(2000);  // 2초 동안 대기
}

void loop() {
  // 현재 루프에서 아무 동작도 하지 않음
}