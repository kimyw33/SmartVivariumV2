
# 스마트 비바리움 강의자료

## 목적
- 본 프로젝트는 비바리움(구체적으로는 테라리움) 제작과 ESP32 개발보드의 활용(IoT 구현을 위한 도구)을 종합하여 스마트 비바리움을 만드는 것을 목표로 합니다.
- 프로젝트를 진행하는 과정에서 "메이킹 활동의 즐거움"을 느끼고, "IoT에 대한 지식과 이해(나아가 적용)"를 쌓길 기대합니다.
- 참고로 본 프로젝트는 개인적으로 개발하는 중인 스마트 비바리움(가칭 SmartVivariumV1, V1)을 강의용으로 개선한 것으로, V1과의 차이는 아래와 같습니다.

---

<details>
  <summary>V1과의 차이</summary>

  **1. ESP32 개발보드 변경**
  - 기존 5 type 포트가 C-type 포트로 변경되었습니다.

  **2. ESP32 확장쉴드 변경**
  - Motor Driver가 내장됨으로써 직류 모터의 활용이 손쉬워졌습니다.

  **3. 연결 케이블의 개선**
  - 꼬임이 덜해졌습니다.

  **4. 쉴드 및 센서 모듈의 변경**
  - Inserted nut 방식으로 나사산이 내장된 구조로 변경되었습니다.

  **5. IoT 데이터 스트림 변경**
  - ThingsBoard에서 Blynk로 변경되어 보다 손쉬운 활용이 가능해졌습니다.

  **[스마트 비바리움 버전1 보기](https://github.com/kimyw33/SmartVivarirumV1/blob/main/)**
</details>

---

## 개발환경 및 준비물
- 무선 네트워크, 구글 계정, Arduino IDE, ESP32 개발보드, 확장 쉴드, 각종 센서 및 액추에이터
- 세부 준비물은 각 소단위 프로젝트에 제시합니다.

---

## 프로젝트의 흐름
1. **1~7 단계 프로젝트:** ESP32, 각종 센서 및 액추에이터의 활용 학습
2. **8단계 프로젝트:** 스마트 비바리움 IoT 파트 구현

- **[스마트 비바리움 H/W 파트 강의자료](https://docs.google.com/presentation/d/12xPUkoJv91gLXm0bsvXzf9R5jyYTA5dgaRWX5TxJ8Es/edit#slide=id.g30a0a790ebb_0_480)**
- **[스마트 비바리움 S/W 파트 강의자료](https://docs.google.com/presentation/d/1XFu0OybRgOFuvAiohChtytxxnoHKm3WtEePIajUeksk)**

---

## 프로젝트 1~7 준비물 및 코드 설명

### 프로젝트 1: 기본 ESP32 설정
- **목표:** ESP32를 설정하고 WiFi에 연결합니다.
- **준비물:** ESP32 개발보드, USB 케이블
- **코드 설명:** 
  - `WiFi.begin()`을 사용해 네트워크에 연결하고, 연결 상태를 시리얼 모니터에 출력합니다.

### 프로젝트 2: LED 제어
- **목표:** ESP32를 사용해 내장 LED를 제어합니다.
- **준비물:** ESP32 개발보드
- **코드 설명:** 
  - `digitalWrite()` 함수를 사용해 LED를 켜고 끕니다.

### 프로젝트 3: 버튼 입력 읽기
- **목표:** 버튼 입력을 읽어 LED 상태를 변경합니다.
- **준비물:** ESP32 개발보드, 버튼, 풀업 저항
- **코드 설명:** 
  - `digitalRead()`를 사용해 버튼 상태를 확인하고, LED를 제어합니다.

### 프로젝트 4: 온습도 센서 (DHT11) 사용
- **목표:** 온도와 습도를 측정하고, 시리얼 모니터에 출력합니다.
- **준비물:** ESP32, DHT11 센서
- **코드 설명:** 
  - `DHT.read()`를 사용해 센서 데이터를 읽고, 온습도 값을 출력합니다.

### 프로젝트 5: 조도 센서 사용
- **목표:** 조도 센서로 주변 밝기를 측정합니다.
- **준비물:** ESP32, 조도 센서
- **코드 설명:** 
  - `analogRead()`를 사용해 조도 값을 읽고, 측정된 값을 Blynk 앱으로 전송합니다.

### 프로젝트 6: NeoPixel LED 제어
- **목표:** NeoPixel LED를 제어하고, 다양한 색상을 표현합니다.
- **준비물:** ESP32, NeoPixel LED
- **코드 설명:** 
  - `Adafruit_NeoPixel` 라이브러리를 사용해 LED의 색상을 설정합니다.

### 프로젝트 7: OLED 디스플레이 사용
- **목표:** OLED 디스플레이에 텍스트를 출력합니다.
- **준비물:** ESP32, SSD1306 OLED 디스플레이
- **코드 설명:** 
  - `Adafruit_SSD1306` 라이브러리를 사용해 텍스트를 출력하고, 센서 데이터를 표시합니다.

---

## 8_스마트 비바리움 프로젝트

### 목표
ESP32, Blynk, 온/습도 센서, 조도 센서, NeoPixel LED, OLED 디스플레이, DC FAN을 이용해 스마트 비바리움 환경을 실시간으로 모니터링하고, Blynk 앱을 통해 원격 제어할 수 있습니다.

<details>
  <summary>준비물</summary>

  * ESP32 보드 1개
  * NeoPixel LED (총 18구)
  * DC FAN 1개
  * SSD1306 OLED 디스플레이
  * 버튼 1개
  * USB 케이블 (ESP32와 PC 연결용)
  * WiFi 네트워크 (SSID 및 비밀번호 필요)
  * Blynk 템플릿 (Blynk 계정 및 인증 토큰 필요)
  * Arduino IDE (코드 작성 및 업로드)
  * 필요한 라이브러리 (Blynk, Adafruit SSD1306 등)
</details>

---

<details>
  <summary>코드 설명</summary>

  - **WiFi 및 Blynk 연결:** `Blynk.begin()`을 사용하여 ESP32가 WiFi 네트워크와 Blynk 서버에 연결됩니다.
  - **온습도 측정:** `dhtEvent()` 함수는 DHT11 센서를 사용해 실시간으로 온도와 습도를 측정합니다.
  - **조도 측정:** `cdsEvent()` 함수는 조도 센서를 통해 빛의 밝기를 측정합니다.
  - **OLED 디스플레이:** `showDisplay()` 함수는 실시간 측정 데이터를 화면에 출력합니다.
  - **LED 및 FAN 제어:** `updateLEDState()`, `updateFANState()` 함수로 제어하며, Blynk 앱이나 버튼을 통해 상태를 변경합니다.
  - **타이머 설정:** `timer.setInterval()` 함수를 사용해 주기적으로 센서 데이터를 읽고, OLED 디스플레이를 갱신합니다.
</details>

---

# 추가 정보
- 연결 상태에 따라 ESP32 내장 LED가 깜빡이며, WiFi 및 Blynk 서버 연결 상태를 시각적으로 확인할 수 있습니다.
- WiFi 연결 시 LED는 1초 간격으로 깜빡이고, 연결되지 않은 경우 LED가 꺼져 있습니다.