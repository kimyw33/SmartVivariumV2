# 스마트 비바리움 강의자료
## 목적
- 본 프로젝트는 비바리움(구체적으로는 테라리움) 제작과 ESP32 개발보드의 활용(IoT 구현을 위한 도구)을 종합하여 스마트 비바리움을 만드는 것을 목표로 합니다.<br>
- 프로젝트를 진행하는 과정에서 "메이킹 활동의 즐거움"을 느끼고, "IoT에 대한 지식과 이해(나아가 적용)"를 쌓길 기대합니다.<br>
- 또한 여기서 멈추는 것이 아닌 보다 아름답고 멋진 스마트 비바리움으로 발전하길 기대하며, 이를 위한 공부를 함께하고 싶습니다.<br>

## 개발환경 및 준비물
- 무선 네트워크 환경, 구글 계정, Arduino IDE가 설치된 PC, ESP32 개발보드, ESP32 개발보드를 효율적으로 사용하기 위한 확장 쉴드, 각종 센서 및 액추에이터, 케이블 등<br>
- 세부 준비물 내역은 아래 소단위 프로젝트마다 제시하였습니다.<br>

## 프로젝트의 흐름
- 00번은 강의자료로서 본 프로젝트를 H/W 중점(테라리움 제작)과 S/W 중점(IoT 활용)으로 구분하여 각각의 pt(presentation) 자료를 공유합니다.<br>
- 다음으로 01~08까지 소단위 프로젝트를 순차적으로 실행해가며, ESP32, 각종 센서 및 액추에이터의 활용 방법, 무선 네트워크를 통한 Blynk 연동 방법 등을 살펴볼 수 있습니다.<br>
- 이후 09번 프로젝트에서는 스마트 비바리움의 IoT 파트를 구현할 수 있도록 구성하였습니다.<br>

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
<details>
  <summary>SmartVivariumV1과의 차이</summary>

  **1. ESP32 개발보드 변경**<br>  
 기존 5 type port가 C-type 포트로 변경되었습니다.

  **2. ESP32 확장쉴드 변경**  
- Motor Drive가 내장됨으로써 직류 모터의 활용이 손쉬워졌습니다.
- 연결 케이블의 개선(잘 꼬이지 않음)이 되었습니다.<br>
- 볼트를 체결할 수 있는 나사산이 추가됨으로써 보드와 이 외의 H/W 연결 시, 너트가 불필요해졌습니다.

  **<a href="https://github.com/kimyw33/SmartVivarirumV1/blob/main/">스마트비바리움 버전1 저장소</a>**

</details>

# 01_BuiltInLedControl