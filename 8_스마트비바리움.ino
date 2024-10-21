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
// float h, t;                  // 습도, 온도 변수이나, 본 프로젝트에서는 활용되지 않음.
int cds_value;                  // 조도 값 변수
bool lastButtonState = LOW;     // 마지막 버튼 상태를 저장하는 변수
bool currentButtonState = LOW;  // 현재 버튼 상태를 저장하는 변수
bool led_state = LOW;           // Blynk 앱에서 제어하는 LED 상태 변수
bool fan_state = LOW;           // Blynk 앱에서 제어하는 FAN 상태 변수

// 온도 및 습도 센서 데이터 읽기 함수
void dhtEvent() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}

// 조도 센서 데이터 읽기 함수
void cdsEvent() {
  cds_value = analogRead(Cds);
  Blynk.virtualWrite(V2, cds_value / 1000);
}

// OLED 디스플레이에 값 출력
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

  String brightness;
  if (cds_value < 820) {
    brightness = "So Dark";
  } else if (cds_value < 1630) {
    brightness = "Dark";
  } else if (cds_value < 2450) {
    brightness = "Normal";
  } else if (cds_value < 3270) {
    brightness = "Bright";
  } else {
    brightness = "So Bright";
  }

  display.println(brightness);
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
  Serial.begin(9600);

  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ;
  }

  dht.begin();  // DHT 센서 초기화
  display.clearDisplay();
  display.display();

  pixels.begin();                     // NeoPixel 초기화
  pinMode(BUTTON_PIN, INPUT_PULLUP);  // 풀업 저항 활성화하여 버튼 핀 설정
  pinMode(FAN_PIN, OUTPUT);           // 릴레이 핀 설정

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, dhtEvent);
  timer.setInterval(500L, cdsEvent);
  timer.setInterval(1000L, showDisplay);
}

void loop() {
  Blynk.run();
  timer.run();
  handleButtonPress();  // 버튼 입력을 계속 확인하여 LED 상태 업데이트
}