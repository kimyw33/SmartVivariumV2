
// WiFi 및 Blynk 관련 상수 정의
#define BLYNK_TEMPLATE_ID "TMPL6F-uJiLbR"                    // Blynk 템플릿 ID, Blynk 클라우드와의 연결을 위해 필요한 고유 ID
#define BLYNK_TEMPLATE_NAME "SmartVivariumV2"                // Blynk 템플릿 이름, 클라우드에서 사용하는 템플릿의 이름
#define BLYNK_AUTH_TOKEN "QFhWpnMI6RYBHF-EtBe89rpkQLcOpPgv"  // Blynk 인증 토큰, 앱에서 생성한 고유 토큰을 사용하여 기기와 서버를 인증함

// 필요한 함수가 정의된 헤더파일 호출
#include <WiFi.h>               // WiFi 연결을 위한 헤더파일 호출
#include <WiFiClient.h>         // WiFi 클라이언트 기능을 제공하는 헤더파일 호출
#include <BlynkSimpleEsp32.h>   // Blynk와 ESP32 연결을 위한 헤더파일 호출
#include <Wire.h>               // I2C 통신을 위한 헤더파일 호출
#include <Adafruit_GFX.h>       // 그래픽 관련 기능을 제공하는 헤더파일 호출
#include <Adafruit_SSD1306.h>   // SSD1306 OLED 디스플레이를 제어하기 위한 헤더파일 호출
#include <DHT.h>                // 온도, 습도 센서를 위한 헤더파일 호출
#include <Adafruit_NeoPixel.h>  // NeoPixel LED 제어를 위한 헤더파일 호출

// WiFi 정보
char ssid[] = "3층 메이커실";  // 연결할 WiFi의 SSID(네트워크 이름)
char pass[] = "ksm1234567";    // 연결할 WiFi의 비밀번호

// OLED 디스플레이 관련 상수 정의
#define SCREEN_WIDTH 128     // OLED 디스플레이의 너비 (픽셀 단위)
#define SCREEN_HEIGHT 64     // OLED 디스플레이의 높이 (픽셀 단위)
#define OLED_RESET -1        // OLED 디스플레이의 리셋 핀 (-1은 리셋 핀 공유를 의미)
#define SCREEN_ADDRESS 0x3C  // I2C 주소 (128x64 OLED 디스플레이의 기본 주소는 0x3C)

// DHT 센서 관련 상수 정의
#define DHTPIN 33      // DHT11 센서가 연결된 핀 번호
#define DHTTYPE DHT11  // 사용 중인 DHT 센서의 종류

// 조도 센서 관련 상수 정의
#define Cds 34  // 조도 센서 핀 번호

// NeoPixel 및 버튼 관련 상수 정의
#define PIN 16         // NeoPixel 스트립을 위한 GPIO 4
#define BUTTON_PIN 32  // 버튼을 위한 GPIO 23
#define FAN_PIN 5      // FAN을 위한 GPIO 5
#define NUMPIXELS 18   // NeoPixel의 픽셀 수

// DHT 센서 설정
DHT dht(DHTPIN, DHTTYPE);  // DHT 객체 생성

// SSD1306 OLED 설정
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);  // OLED 객체 생성

// NeoPixel 설정
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);  // NeoPixel 객체 생성

// 타이머 설정
BlynkTimer timer;  // Blynk 타이머

// 변수 선언
float h, t;                     // 습도, 온도 값을 저장하는 변수
int cds_value;                  // 조도 값을 저장하는 변수
int cds_level;                  //조도 값을 5단계로 구분한 값을 저장하는 변수
String brightness;              // 조도 레벨에 따른 출력 문자를 저장하는 변수
bool lastButtonState = LOW;     // 마지막 버튼 상태를 저장하는 변수
bool currentButtonState = LOW;  // 현재 버튼 상태를 저장하는 변수
bool led_state = LOW;           // LED의 작동 상태를 저장하는 변수
bool fan_state = LOW;           // FAN의 작동 상태를 저장하는 변수

// 온도 및 습도 센서 데이터 읽기 함수
void dhtEvent() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}

// 조도 센서 데이터 읽기 함수
void cdsEvent() {
  cds_value = analogRead(Cds);         // 조도 센서에서 아날로그 형태의 조도 값을 읽어 cds_value 변수에 저장
  cds_level = getCdsLevel(cds_value);  // 조도 값을 5단계로 나눈 값(조도 레벨)을 구하는 함수 호출
  Blynk.virtualWrite(V2, cds_level);
}

// 조도 값에 따른 레벨(0~4)을 구하고 반환하는 함수
int getCdsLevel(int cds_value) {
  if (cds_value < 820) {
    return 0;  // 조도 값이 820 미만일 때 레벨 0 반환
  } else if (cds_value < 1639) {
    return 1;  // 조도 값이 820 이상 1639 미만일 때 레벨 1 반환
  } else if (cds_value < 2458) {
    return 2;  // 조도 값이 1639 이상 2458 미만일 때 레벨 2 반환
  } else if (cds_value < 3277) {
    return 3;  // 조도 값이 2458 이상 3277 미만일 때 레벨 3 반환
  } else {
    return 4;  // 조도 값이 3277 이상일 때 레벨 4 반환
  }
}

// OLED 디스플레이에 값 출력을 제어하는 함수
void showDisplay() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Smart Vivarium");

  display.setTextSize(2);
  display.print("T: ");
  display.print(t);
  display.println(" C");

  display.print("H: ");
  display.print(h);
  display.println(" %");

  // cds_level에 따른 모니터 출력값을 변수 brightness에 저장하는 조건문
  switch (cds_level) {
    case 0:
      brightness = "So dark";  // 레벨이 0일 때, 매우 어두움(So dark)으로 설정
      break;
    case 1:
      brightness = "dark";  // 레벨이 1일 때, 어두움(dark)으로 설정
      break;
    case 2:
      brightness = "Normal";  // 레벨이 2일 때, 보통(Normal)으로 설정
      break;
    case 3:
      brightness = "Bright";  // 레벨이 3일 때, 밝음(Bright)으로 설정
      break;
    case 4:
      brightness = "So bright";  // 레벨이 4일 때, 매우 밝음(So Bright)으로 설정
      break;
    default:
      brightness = "Unknown";  // 예외 처리(측정 범위를 벗어났을 경우)
      break;
  }
  display.println(brightness);  // cds_level에 따른 문자 출력
  display.setTextSize(1);
  display.print("by kimyw33");
  display.display();
}

// NeoPixel LED 제어 함수 (Blynk 앱 및 버튼 제어)
void updateLEDState() {
  pixels.clear();
  if (led_state) {
    for (int i = 0; i < NUMPIXELS; i++) {
      if (i % 2) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));  // 짝수 빨간색
      } else {
        pixels.setPixelColor(i, pixels.Color(0, 0, 255));  // 홀수 파란색
      }
    }
  } else {
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));  // 모든 LED 끔
    }
  }
  pixels.show();  // NeoPixel 업데이트
}

// 팬 제어 함수
void updateFANState() {
  if (fan_state) {
    digitalWrite(FAN_PIN, HIGH);  // 팬 ON
  } else {
    digitalWrite(FAN_PIN, LOW);  // 팬 OFF
  }
}

// 버튼을 통한 LED 제어 함수
void handleButtonPress() {
  currentButtonState = digitalRead(BUTTON_PIN);                // 버튼 상태 읽기
  if (currentButtonState == LOW && lastButtonState == HIGH) {  // 버튼이 눌릴 때
    led_state = !led_state;                                    // LED 상태 토글
    Blynk.virtualWrite(V3, led_state);                         // Blynk 앱으로 LED 상태 전송
    updateLEDState();                                          // LED 상태 업데이트
    //fan_state = !fan_state;                                  // FAN 상태 토글 코드이나, LED와 FAN을 동시 제어하지 않으므로 주석 처리
    //Blynk.virtualWrite(V4, fan_state);                       // Blynk 앱으로 FAN 상태 전송 코드이나, LED와 FAN을 동시 제어하지 않으므로 주석 처리
    //updateFANState();                                        // FAN 상태 업데이트 코드이나, LED와 FAN을 동시 제어하지 않으므로 주석 처리
  }
  lastButtonState = currentButtonState;  // 버튼 상태 업데이트
}

// Blynk V3 핸들러 (LED 제어)
BLYNK_WRITE(V3) {
  led_state = param.asInt();  // Blynk 앱에서 V3 핀으로 값을 받음
  updateLEDState();           // NeoPixel LED 제어
}

// Blynk V4 핸들러 (팬 제어)
BLYNK_WRITE(V4) {
  fan_state = param.asInt();  // Blynk 앱에서 V4 핀으로 값을 받음
  updateFANState();           // 팬 상태 제어
}

void setup() {
  Serial.begin(9600);  // 시리얼 통신 속도를 9600 baud rate로 설정

  // 디스플레이 초기화 실패 시, 에러메시지("SSD1306 aloocation failed" 출력 후, 멈춤(무한루프) 실행
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  dht.begin();             // DHT 센서 초기화
  display.clearDisplay();  // 디스플레이 지우기
  display.display();       // 디스플레이를 업데이트하여 화면에 반영

  pixels.begin();                     // NeoPixel 초기화
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 풀업 저항 활성화하여 버튼 핀 설정
  pinMode(FAN_PIN, OUTPUT);           // Fan 핀 설정

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);  // Blynk 서버에 접속하여 원격 제어 준비

  timer.setInterval(1000L, dhtEvent);     // 1초마다 온습도 센서 실행
  timer.setInterval(1000L, cdsEvent);     // 1초마다 조도 센서 실행
  timer.setInterval(1000L, showDisplay);  // 1초마다 디스플레이 갱신
}

void loop() {
  Blynk.run();          // Blynk 서버와 통신을 실행
  timer.run();          // timer 실행
  handleButtonPress();  // 버튼 입력을 계속 확인하여 LED 상태 업데이트
}