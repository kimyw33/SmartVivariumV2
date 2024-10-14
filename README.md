# 스마트 비바리움 강의자료
## 목적
- 본 프로젝트는 비바리움(구체적으로는 테라리움) 제작과 ESP32 개발보드의 활용(IoT 구현을 위한 도구)을 종합하여 스마트 비바리움을 만드는 것을 목표로 합니다.
- 프로젝트를 진행하는 과정에서 "메이킹 활동의 즐거움"을 느끼고, "IoT에 대한 지식과 이해(나아가 적용)"를 쌓길 기대합니다.
- 참고로 본 프로젝트는 개인적으로 개발하는 중인 스마트 비바리움(가칭 SmartVivariumV1, V1)을 강의용으로 개선한 것으로, V1과의 차이는 아래와 같습니다.

<details>
  <summary>V1과의 차이</summary>

  **1. ESP32 개발보드 변경**
 - 기존 5 type 포트가 C-type 포트로 변경되었습니다.

  **2. ESP32 확장쉴드 변경**  
- Motor Drive가 내장됨으로써 직류 모터의 활용이 손쉬워졌습니다.
- 연결 케이블의 개선(잘 꼬이지 않음)이 되었습니다.
- 볼트를 체결할 수 있는 나사산이 추가됨으로써 보드와 이 외의 H/W 연결 시, 너트가 불필요해졌습니다.

  **<a href="https://github.com/kimyw33/SmartVivarirumV1/blob/main/">스마트비바리움 버전1 보기</a>**
</details>

## 개발환경 및 준비물
- 무선 네트워크 환경, 구글 계정, Arduino IDE가 설치된 PC, ESP32 개발보드, ESP32 개발보드를 효율적으로 사용하기 위한 확장 쉴드, 각종 센서 및 액추에이터, 케이블 등<br>
- 세부 준비물 내역은 아래 소단위 프로젝트마다 제시하였습니다.<br>

## 프로젝트의 흐름
- 0번은 강의자료로서 본 프로젝트를 H/W 중점(테라리움 제작)과 S/W 중점(IoT 활용)으로 구분하여 각각의 pt(presentation) 자료를 공유합니다.<br>
- 다음으로 1~8까지 소단위 프로젝트를 순차적으로 실행해가며, ESP32, 각종 센서 및 액추에이터의 활용 방법, 무선 네트워크를 통한 Blynk 연동 방법 등을 살펴볼 수 있습니다.<br>
- 이후 9번 프로젝트에서는 스마트 비바리움의 IoT 파트를 구현할 수 있도록 구성하였습니다.<br>

<details>
  <summary>환경 구축(최초 1회 수행)</summary>
  1. OS에 맞는 Arduino IDE 설치
  <a href="https://www.arduino.cc/en/software">설치 링크</a><br>
  2. 필요한 경우 시스템 언어 변경(File/Arduino IED->Preferences->재시작)<br>
  3. 기본 설정->추가 보드 관리자 URL->"비공식 보드 지원 URL 목록을 보려면 클릭하십시오." 클릭->"Espressif ESP32" 검색->해당 "*.json"파일 복사/붙여넣기 후 확인<br>
  4. 보드 매니저->"esp32 by Espressif Systems"설치<br>
  5. PC와 ESP32 연결<br>
  6. 보드 및 포트를 아래와 같이 연결<br>
     - 보드: DOIT ESP32 DEVKIT V1<br>
     - 포트: Serial Port(USB), 포트 번호는 COM4, COM3 등으로 다를 수 있음.<br>
  7. ESP32 업로드 에러 발생 시
  <a href="https://docs.google.com/presentation/d/1MqSPEBPEWeh-agVcmBz7CRioSePWG-13oV_nJNzy-uo/edit?usp=sharing">문제 해결 방법</a>
</details>

# 1_내장 LED 제어

이 프로젝트의 목표는 **ESP32 보드가 제대로 작동하는지 확인**하는 것입니다. 이를 위해 **내장된 LED를 제어**하여 **1초 간격**으로 켜고 끄는 동작을 실행시킵니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - Arduino IDE(코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  이 실습에서는 ESP32 내장 LED를 활용하여 간단한 점멸 제어를 수행합니다.<br>
  GPIO 2번 핀에 연결된 내장 LED를 1초마다 켜고 끄는 동작을 반복하게 됩니다.<br>
</details>

---

# 2_조도 센서 활용

이 프로젝트의 목표는 ESP32와 조도 센서(Cds)를 이용하여 주변 빛의 양을 측정하고, 측정된 값을 시리얼 모니터를 통해 확인하는 것입니다.<br>
이를 통해 빛이 얼마나 밝고 어두운지를 실시간으로 확인할 수 있으며, 이를 바탕으로 **밝기에 따른 LED 제어** 실습을 수행하게 됩니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - 조도 센서(Cds) 1개<br>
  - 점퍼 와이어(쉴드와 조도 센서 모듈 연결용) 1개<br>
  - Arduino IDE(코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - 쉴드의 입력 전용(Input Only) 중, GPIO 34번 핀을 사용하여 조도 센서의 값을 아날로그 신호 형태로 읽어들입니다.<br>
  - 읽어들인 아날로그 값(0 ~ 4095)은 빛의 양에 따라 변화하며, 값이 낮을수록 어두운 상태, 값이 높을수록 밝은 상태를 의미합니다.<br>
  - 시리얼 모니터를 통해 실시간으로 주변 환경의 밝기를 모니터링합니다.<br>
</details>

**2-1_조도 센서 응용**<br>
- 본 응용 프로젝트의 목표는 ESP32와 조도 센서를 사용하여 주변의 빛의 밝기를 측정하고, 그 값을 5단계로 구분하여 시리얼 모니터에 출력하는 것입니다.<br>
- 이를 바탕으로 최종 프로젝트에서는 "밝고 어두운 정도에 따른 LED ON/OFF제어" 실습을 수행하게 됩니다.

---

# 3_온/습도 센서 활용

이 프로젝트의 목표는 **ESP32와 온/습도센서**를 사용하여 **주변 환경의 온도와 습도를 측정**하고, 그 값을 **시리얼 모니터**를 통해 실시간으로 확인하는 것입니다.<br>
이를 바탕으로 "실시간으로 측정된 온도와 습도값을 OLED 및 App에서 확인하는" 실습을 수행하게 됩니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - 온/습도 센서(DHT11) 1개
  - 점퍼 와이어(쉴드와 온/습도 센서 모듈 연결용) 1개<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - DHT 라이브러리(Arduino IDE에서 설치, 본 실습에서는 "DHT sensor library" by Adafruit 사용)
</details>

<details>
  <summary>코드 설명</summary>
  - GPIO 33번 핀에 연결된 DHT11 센서로부터 온도와 습도 데이터를 읽어들입니다.<br>
  - 'DHT.h'헤더파일에 포함된 `dht.readTemperature()` 함수로 온도 값을, `dht.readHumidity()` 함수로 습도 값을 읽습니다.<br>
  - 읽어들인 값은 시리얼 모니터를 통해 출력되며, DHT11 센서는 특성 상 최소 2초 이상의 지연이 필요하므로, 'delay(2000)'를 사용합니다.<br>
</details>

---

# 4_OLED 제어

이 프로젝트의 목표는 **I2 통신C**을 통해 **OLED 디스플레이**에 특정 텍스트를 출력하는 것입니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - 128x64 OLED 디스플레이(SSD1306) 1개
  - 점퍼 와이어(쉴드와 OLED 모듈 연결용, 4핀) 1개<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - Adafruit BusIO, Adafruit GFX 및 Adafruit SSD1306 라이브러리(Arduino IDE에서 설치, 본 실습에서는 "Adafruit SSD1306" by Adafruit 사용)
</details>

<details>
  <summary>코드 설명</summary>
  - I2C 통신을 사용하여 SSD1306 OLED 디스플레이에 텍스트를 출력합니다.<br>
  - 디스플레이의 해상도(128x64)를 설정하고, 디스플레이 객체를 초기화한 후 텍스트를 출력합니다.<br>
  - 텍스트는 총 4줄로 구성되어 있으며, "Smart Vivarium Test"와 "프로젝트 제작자 이름/닉네임"을 포함합니다.<br>
  - 'display.clearDisplay()'로 화면을 지우고(초기화), "display.setTextSize(2)"로 텍스트 크기를 두 배로 설정합니다.<br>
  - 'display.println()'과 'display.print()'를 사용하여 각 줄에 텍스트를 출력하며, 'display.display()'를 호출하여 내용을 OLED 화면에 텍스트를 출력합니다.<br>
  - 또한 프로그램이 정상적으로 작동하지 않을 경우, 시리얼 모니터에 오류 메시지를 출력한 후 무한 루프에 빠져 오류를 디버깅할 수 있게 설정되어 있습니다.<br>
</details>

**4-1_OLED 제어 응용**<br>
  - 본 응용 프로젝트의 목표는 위에서 살펴본 OLED에 Cds, DHT11 센서로 읽어들인 값을 출력함으로써 현재의 온도, 습도 및 밝기 정도(5단계)를 실시간으로 모니터링하는 것입니다.

  ---

# 5_버튼 제어

이 프로젝트의 목표는 **버튼의 상태를 읽고 시리얼 모니터에 출력**하는 것입니다.<br>
참고) 버튼을 눌렀을때: 1, 누르지 않았을때: 0

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - BUTTON 모듈 1개
  - 점퍼 와이어(쉴드와 BUTTON 모듈 연결용) 1개<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
</details>

<details>
  <summary>코드 설명</summary>
  - 버튼 핀 설정: 'pinMode(BUTTON, INPUT)'을 사용하여 버튼 핀을 입력 모드로 설정합니다.<br>
  - 버튼 상태 읽기: 'digitalRead(BUTTON)'으로 버튼 핀의 디지털 입력 값을 읽어옵니다.<br>
  - 버튼 상태 출력: 읽어온 버튼 상태를 'Serial.println(buttonState)'을 사용하여 시리얼 모니터에 출력합니다.<br>
  - 디바운싱: 'delay(100)'을 사용하여 버튼 상태를 읽는 간격을 0.1초로 설정하여 입력 노이즈를 방지합니다.<br>
</details>

**5-1_버튼 제어 응용**<br>
- 본 응용 프로젝트의 목표는 버튼을 마치 ON / OFF 스위치 처럼 "한 번 눌렀을 때 버튼 상태를 0->1 또는 1->0로 유지하는 것"입니다.<br>
- 버튼이 눌릴 때마다 토글(Toggle)하여 현재의 상태를 시리얼 모니터에 출력합니다.<br>

 ---

 # 06_ButtonControlLed

 이 프로젝트의 목적은 위에서 살펴본 **BUTTON을 활용**하여 **NeoPixel LED 스트립의 전원을 제어**하는 것입니다.<br>
 버튼을 눌렀을 때, NeoPixel LED가 켜지며, 버튼을 다시 누르면 NeoPixel LED 꺼집니다.<br>
추가로 NeoPixel Led의 색상은 식물의 광합성에 가장 효율적인 **청색**과 **적색**으로 설정하였습니다.<br>
참고) 본 프로젝트에서 제작할 비바리움의 크기(200x200x200)를 고려하여 LED(9구)*2개 = 18구를 직렬 연결(모듈 1개의 OUT 단자와 추가한 모듈의 IN 단자를 연결)하여 사용하였습니다. LED 출력 개수를 변경하고자 할 경우 'NUMPIXELS 18'의 개수 부분을 필요한 만큼 변경 가능합니다.

<details>
  <summary>준비물</summary>
  - ESP32 보드 1개<br>
  - EPS32 쉴드(DOIT ESP32 DEVKIT V1) 1개<br>
  - USB 케이블(ESP32와 PC 연결용) 1개<br>
  - BUTTON 모듈 1개
  - NeoPixel LED 스트립 모듈 2개(픽셀 수: 9구*2개 = 총 18구)<br>
  - 점퍼 와이어(쉴드와 BUTTON 모듈, LED 모듈 연결용) 총 3개<br>
  - Arduino IDE (코드 작성 및 업로드)<br>
  - Adafruit NeoPixel 라이브러리(Arduino IDE에서 설치, 본 실습에서는 "Adafruit NeoPixel" by Adafruit 사용)
</details>

<details>
  <summary>코드 설명</summary>
  - 버튼 상태 읽기: `digitalRead(BUTTON_PIN)`을 사용하여 버튼의 현재 상태를 읽어옵니다.<br>
  - 버튼 상태 변화 감지: 버튼의 상태가 변화했는지 확인하고, 상태가 `HIGH`일 때 LED 상태를 토글합니다.<br>
  - LED 색상 설정: `isOn` 변수에 따라 LED의 색상을 설정합니다. 버튼이 눌리면 짝수 인덱스의 LED를 빨간색으로, 홀수 인덱스의 LED를 파란색으로 설정합니다. 버튼이 눌리지 않으면 모든 LED를 꺼서 LED를 끕니다.<br>
  - 디바운싱: 버튼 입력의 노이즈를 방지하기 위해 짧은 지연을 추가합니다.<br>
</details>

<details>
  <summary>모터 드라이버가 내장된 쉴드에서 팬(FAN)을 활용하고자 할 경우</summary>
- 모터 드라이버가 지원되는 GPIO 중, DC 팬을 5번 핀에 연결된 상황 가정<br>
- 위 '6_버튼으로 LED 제어'에서 LED의 ON / OFF와 동기화하여 FAN 작동하도록 설정<br>
- 코드:<br>
#include <Adafruit_NeoPixel.h>  // NeoPixel 스트립을 제어하기 위한 헤더파일 호출

#define PIN 16         // NeoPixel 스트립을 위한 GPIO 16
#define BUTTON_PIN 32  // 버튼을 위한 GPIO 32
#define NUMPIXELS 18   // NeoPixel의 픽셀 수
#define FAN_PIN 5      // FAN을 위한 GPIO 5

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

bool ledState = false;          // LED 상태를 저장하는 변수
bool fanState = false;
bool lastButtonState = LOW;     // 마지막 버튼 상태를 저장하는 변수
bool currentButtonState = LOW;  // 현재 버튼 상태를 저장하는 변수

void setup() {
  pinMode(BUTTON_PIN, INPUT);  // 버튼 핀을 입력 모드로 설정합니다.
  // 버튼을 눌렀을 때, Led가 오작동하거나, 깜빡깜빡 거릴 경우, 위 코드를 주석처리하고, 아래 코드의 주석을 제거하여 코드 작성
  //pinMode(BUTTON_PIN, INPUT_PULLUP);  // 버튼 핀을 풀업 저항과 함께 입력 모드로 설정
  pixels.begin();  // NeoPixel 스트립을 초기화합니다.
  pinMode(FAN_PIN, OUTPUT);    // 팬 핀을 출력 모드로 설정합니다.
}

void loop() {
  currentButtonState = digitalRead(BUTTON_PIN);  // 현재 버튼 상태를 읽어 currentButtonState 변수에 저장합니다.

  // 버튼 상태가 변화한 경우
  if (currentButtonState != lastButtonState) {
    // 버튼이 눌렸을 때 상태를 변경합니다.
    if (currentButtonState == HIGH) {
      ledState = !ledState;  // LED 상태를 토글합니다.
      fanState = !fanState;  // FAN 상태를 토글합니다.
    }
    delay(50);  // 버튼 상태 변화에 대한 노이즈를 방지하기 위한 짧은 지연
  }

  // LED 상태에 따라 NeoPixel 색상을 설정합니다.
  if (ledState) {
    for (int i = 0; i < NUMPIXELS; i += 2) {
      pixels.setPixelColor(i, pixels.Color(255, 0, 0));  // 짝수 픽셀을 빨간색으로 설정합니다.
    }
    for (int i = 1; i < NUMPIXELS; i += 2) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));  // 홀수 픽셀을 파란색으로 설정합니다.
    }
    pixels.show();  // 색상 변경 사항을 디스플레이합니다.
    digitalWrite(FAN_PIN, HIGH);  // 팬을 켭니다.
  } else {
    pixels.clear();  // 모든 픽셀을 꺼서 LED를 끕니다.
    pixels.show();   // 색상 변경 사항을 디스플레이합니다.
    digitalWrite(FAN_PIN, LOW);  // 팬을 끕니다.
  }

  lastButtonState = currentButtonState;  // 마지막 버튼 상태를 현재 상태로 업데이트합니다.
  delay(100);                            // 버튼 디바운싱을 위한 지연
}<br>


---

# 07_ConnetingToBlynkByWifi