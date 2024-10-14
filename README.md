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

# 05_Button