# ESP32 Digital Ohmmeter & Voltmeter
> A precision resistance and voltage measurement device built on the ESP32 microcontroller, featuring real-time OLED display via I2C and nonlinearity correction for the onboard 12-bit ADC.
![z7716042692885_a50d0d34f0f6eb07ac7dab6c8332fa82](https://github.com/user-attachments/assets/770851da-dd9c-4fac-a185-180c0f3a0bf8)

## Table of Contents

[Overview](#overview)
[Hardware](#hardware)
[Key Concepts](#key-concepts)
[Implementation](#implementation)
[Results](#results)
[Lessons Learned](#lessons-learned)
[Strengths & Limitations](#strengths--limitations)
[Upgrade Path](#upgrade-path)


## Overview
This project explores the practical capabilities and limitations of the ESP32's onboard 12-bit ADC by building a functional dual-mode measurement tool. The device measures unknown resistance values using a voltage divider circuit and can switch to direct voltage measurement mode via a physical button.
Core challenges addressed:

- Handling the nonlinear ADC response inherent to the ESP32 chip
- Reducing noise through oversampling (64-sample averaging)
- Displaying stable, real-time data over I2C to an SSD1306 OLED

## Hardware
| Component | Specification | 
| ----- | ----------------- |
| Microcontroller | ESP32 DevKit V1 — 240 MHz, 3.3 V, 12-bit ADC (0–4095) |
| Display | 0.96" OLED SSD1306 — 128×64 px, I2C protocol | 
| Reference Resistor | 5 kΩ | 
|Input Pin| GPIO35 |
| Display Bus | GPIO21 (SDA) / GPIO22 (SCL) | 
| Mode Button | GPIO4 (INPUT_PULLUP) |

![z7716042683275_01e946cb15bc3f0dfebfcf33478da4f0](https://github.com/user-attachments/assets/16263b02-8d6b-4337-83d5-86d27f9404d0)

## Key Concepts
### ADC — Analog-to-Digital Conversion
The ESP32's 12-bit ADC divides the 0–3.3 V input range into 4096 discrete levels (2¹² = 4096). Each GPIO ADC pin converts a continuous analog voltage into an integer the microcontroller can process.


<img width="1216" height="891" alt="DATASHEET_ESP32" src="https://github.com/user-attachments/assets/ba58c448-65d6-4f93-9db5-be83d4b46cac" />

> Known limitation: The ESP32 ADC is not perfectly linear — it saturates near 0 V and 3.3 V and has a nonlinear response curve in between. Software calibration is required for accurate readings.


   <img width="1246" height="882" alt="Screenshot 2026-04-12 202140" src="https://github.com/user-attachments/assets/3f30bd9c-aa7a-4593-bf93-dc2496ba1a5e" />

### I2C — Inter-Integrated Circuit
I2C enables the ESP32 (Master) to communicate with the OLED display (Slave) over just two wires:
| Wire | Function |
| --- | ---| 
| SDA | Bidirectional serial data |
|SCL | Clock signal for synchronization |
   
   <img width="600" height="167" alt="Screenshot 2026-04-11 224838" src="https://github.com/user-attachments/assets/7db5712e-5efc-4c3b-a873-b598b0c7e67c" />
   
Multiple devices can share the same bus and are distinguished by unique 7-bit addresses — conserving GPIO pins for other use.
   
# Implementation
## 1 — Circuit Design (Wokwi Simulation)
The circuit was prototyped in Wokwi before physical assembly to validate wiring and logic without risk to components.

   <img width="1259" height="642" alt="Screenshot 2026-04-11 230830" src="https://github.com/user-attachments/assets/f19d6697-6c9f-4290-b864-f66d412105ae" />
Resistance measurement mode uses a classic voltage divider:
```
3.3V ──[ R_ref (5kΩ) ]──┬──[ R_unknown ]── GND
                         │
                       GPIO35 (ADC)
```
Voltage measurement mode connects the test leads directly to GPIO35 and GND.

> Safety note: GPIO35 has a maximum input of 3.3 V. Exceeding this will permanently damage the chip. For measuring higher voltages, use a dedicated voltage divider module or an ADS1115 external ADC.
  
## 2 — Software & Algorithm
### Button handling — INPUT_PULLUP
Using INPUT_PULLUP activates the ESP32's internal pull-up resistor, keeping the pin at a stable HIGH by default. This eliminates the need for an external resistor and prevents floating-state errors.
```cpp
  pinMode(BUTTON_PIN, INPUT_PULLUP);
```
  
   <img width="665" height="492" alt="Screenshot 2026-04-12 215134" src="https://github.com/user-attachments/assets/33e18641-441e-4659-9932-0f84056c46ae" />

        
   <img width="559" height="193" alt="Screenshot 2026-04-12 214738" src="https://github.com/user-attachments/assets/78ba7352-40d3-42f7-b774-1e23186f8d3c" />

 ### Oversampling for noise reduction
Instead of reading a single ADC value, the firmware averages 64 consecutive samples to suppress electrical noise and produce a stable output:
```cpp     long sum = 0;
for (int i = 0; i < 64; i++) {
    sum += analogRead(ADC_PIN);
}
float adc_avg = sum / 64.0;
```
     
   <img width="1033" height="1024" alt="Gemini_Generated_Image_9mcjx89mcjx89mcj" src="https://github.com/user-attachments/assets/60f62a93-0fe1-436f-a15c-91ceab7ae627" />
        
 ### Resistance calculation
From the voltage divider equation:
```
V_adc = V_supply × R_unknown / (R_ref + R_unknown)
```
Rearranged to solve for the unknown resistance:
```
R_unknown = R_ref × ADC_value / (4095 - ADC_value)
```
A nonlinearity correction factor is then applied in software to compensate for the ESP32 ADC's response curve and minimize measurement error.
      
   <img width="395" height="131" alt="Screenshot 2026-04-12 220756" src="https://github.com/user-attachments/assets/c3342d6f-6d1e-456e-b5ea-365eb6447b1b" />

       
 
      
   <img width="438" height="150" alt="Screenshot 2026-04-12 220902" src="https://github.com/user-attachments/assets/77e72ff7-b07d-4107-a844-0a33df9f659b" />

     
     
  <img width="484" height="147" alt="Screenshot 2026-04-12 220950" src="https://github.com/user-attachments/assets/e0608a74-2a1c-4c18-a35f-75b8de19dd89" />

  

# Results 
  ![z7716042699872_9a72740c4d3ad3730f162f772874d8e9](https://github.com/user-attachments/assets/6eb6f385-009f-4ba7-95a5-efe3106a1006)
  ![z7716042691230_51affcfee0bffc5749a97acb38eb92a6](https://github.com/user-attachments/assets/d039147c-4d1c-4620-9e43-3f81e94ebda4)
  ![z7716042692215_7896b5b049b080c4da5bbb066ab3572c](https://github.com/user-attachments/assets/37a427f1-df17-415d-9d69-57dae2d68be7)

# Lessons Learned
## 1. ADC behavior in practice
The theoretical 12-bit resolution does not mean 12-bit accuracy. Real-world ADC readings are affected by power supply noise, chip temperature, and the inherent nonlinearity of ESP32's SAR ADC design. Oversampling and calibration are non-negotiable for stable results.
## 2. I2C efficiency
Driving the OLED over I2C with only 2 GPIO pins freed up significant resources. Understanding I2C addressing also opened the door to chaining multiple peripherals on the same bus.
## 3. Simulation-first workflow
Prototyping in Wokwi before touching real hardware dramatically reduced the risk of component damage and shortened the debug cycle. This practice translates directly to professional embedded development workflows.
## 4. Structured code organization
Splitting the firmware into separate .ino tab files (ADC logic, display rendering, button handling) made the codebase cleaner, easier to debug, and ready to extend.
# Strengths & Limitations
| | |
|---|---|
| ✅ Processing speed | 240 MHz CPU handles averaging and display refresh with negligible latency |
| ✅ Connectivity | Built-in Wi-Fi & Bluetooth make IoT upgrades straightforward |
| ✅ Cost-effectiveness | 12-bit ADC at a fraction of the cost of dedicated measurement ICs |
| ❌ ADC nonlinearity | Response curve is nonlinear, especially near rail voltages; software correction required |
| ❌ Internal noise | Active Wi-Fi/Bluetooth modules introduce ADC noise; requires filtering capacitors or algorithm compensation |
| ❌ Voltage limit | Maximum safe input is 3.3 V — unsuitable for direct mains or high-voltage measurement|
# Upgrade Path

| Need | Recommendation |
|---|---|
| Higher ADC accuracy | Replace onboard ADC with **ADS1115** — keeps ESP32 speed, adds measurement precision |
| True linear ADC | Switch MCU to **STM32 series** series — significantly better ADC linearity out of the box|
| Higher voltage range | Add a precision resistor voltage divider module or dedicated isolation frontend |
| Remote monitoring | Leverage ESP32's Wi-Fi to push readings to an MQTT broker or simple web dashboard |
# Tech Stack

`C++ / Arduino Framework` · `ESP32 DevKit V1` · `SSD1306 OLED`

---

*If you found this project useful, feel free to open an Issue or leave a Star ⭐*

