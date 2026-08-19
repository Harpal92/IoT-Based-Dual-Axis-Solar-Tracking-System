# IoT-Based Dual-Axis Solar Tracking System

## 📌 Overview

This project is an **IoT-based dual-axis solar tracking system** designed to automatically orient a solar panel toward the direction of maximum light intensity.

The system uses **four LDR (Light Dependent Resistor) sensors** to detect the relative direction of the light source and **two servo motors** to control the panel in two axes:

* **Azimuth:** Horizontal / left-right movement
* **Elevation:** Vertical / up-down movement

An **Arduino UNO** processes the LDR readings and controls the servo motors. An **ESP8266 NodeMCU** is used for Wi-Fi connectivity and IoT-based monitoring through **ThingSpeak**.

---

## 🎯 Objectives

* Automatically track the direction of maximum light intensity.
* Control the solar panel in both horizontal and vertical directions.
* Use sensor feedback for automatic positioning.
* Monitor sensor data remotely using IoT.
* Develop a low-cost embedded-system prototype.
* Provide a foundation for future solar-energy measurement and optimization.

---

## 🏗️ System Architecture

```text
                 ┌─────────────────────┐
                 │     4 × LDR         │
                 │      Sensors        │
                 └──────────┬──────────┘
                            │
                            ▼
                 ┌─────────────────────┐
                 │     Arduino UNO     │
                 │ Sensor Processing   │
                 │ & Motor Control     │
                 └──────────┬──────────┘
                            │
                 ┌──────────┴──────────┐
                 ▼                     ▼
          ┌─────────────┐       ┌─────────────┐
          │   Servo X   │       │   Servo Y   │
          │   Azimuth   │       │  Elevation  │
          └─────────────┘       └─────────────┘

                            │
                     Sensor Data
                            ▼
                 ┌─────────────────────┐
                 │ ESP8266 NodeMCU     │
                 │   Wi-Fi Module      │
                 └──────────┬──────────┘
                            │
                         Internet
                            │
                            ▼
                 ┌─────────────────────┐
                 │     ThingSpeak      │
                 │   IoT Monitoring     │
                 └─────────────────────┘
```

---

## 🔧 Hardware Components

| Component          |    Quantity | Purpose                                 |
| ------------------ | ----------: | --------------------------------------- |
| Arduino UNO        |           1 | Main controller and motor control       |
| ESP8266 NodeMCU    |           1 | Wi-Fi and IoT communication             |
| LDR Sensor         |           4 | Light-intensity sensing                 |
| 10kΩ Resistor      |           4 | LDR voltage-divider circuits            |
| Servo Motor        |           2 | Dual-axis movement                      |
| Breadboard         |           1 | Circuit prototyping                     |
| Jumper Wires       | As required | Electrical connections                  |
| External 5V Supply |           1 | Recommended power source for two servos |

---

## 🔌 Pin Configuration

### LDR Sensors

| LDR  | Arduino Pin |
| ---- | ----------- |
| LDR1 | A0          |
| LDR2 | A1          |
| LDR3 | A2          |
| LDR4 | A3          |

### Servo Motors

| Motor   | Arduino Pin | Function                      |
| ------- | ----------- | ----------------------------- |
| Servo X | D9          | Azimuth / horizontal movement |
| Servo Y | D10         | Elevation / vertical movement |

---

## 💡 LDR Circuit

Each LDR is connected as a voltage divider with a **10kΩ resistor**.

```text
5V
 │
[LDR]
 │
 ├──────── Arduino Analog Pin
 │
[10kΩ]
 │
GND
```

The voltage at the analog input changes according to the amount of light received by the LDR.

---

## ⚙️ Working Principle

Four LDR sensors are positioned around the panel.

The Arduino continuously reads:

```text
LDR1 → A0
LDR2 → A1
LDR3 → A2
LDR4 → A3
```

The sensor values are compared to determine the direction in which the light intensity is higher.

### Horizontal Tracking

The difference is calculated as:

```text
diffX = LDR1 - LDR2
```

If the difference is greater than the predefined threshold, the horizontal servo changes its position.

### Vertical Tracking

The difference is calculated as:

```text
diffY = LDR3 - LDR4
```

If the difference exceeds the threshold, the vertical servo changes its position.

A threshold is used to reduce unnecessary servo movement caused by small differences and sensor variations.

Servo positions are constrained between:

```text
0° and 180°
```

---

## 💻 Arduino Implementation

The Arduino program uses the `Servo` library.

The main process is:

```text
Read 4 LDR values
       ↓
Calculate horizontal difference
       ↓
Calculate vertical difference
       ↓
Check tracking threshold
       ↓
Update Servo X and Servo Y
       ↓
Repeat
```

The complete Arduino implementation is available in:

```text
Arduino/dual_axis_tracker.ino
```

---

## 🌐 IoT Implementation

The ESP8266 NodeMCU provides Wi-Fi connectivity.

The NodeMCU connects to a configured Wi-Fi network and communicates with **ThingSpeak**.

Sensor data can be sent to ThingSpeak fields for remote monitoring and visualization.

The IoT implementation is available in:

```text
ESP8266/thingspeak_iot.ino
```

### Security Note

Wi-Fi credentials and ThingSpeak API keys are intentionally excluded from the public repository.

Users should configure their own credentials locally.

---

## 🔋 Servo Power Supply

Two servo motors can require significantly more current than the Arduino UNO should be expected to provide through its 5V output.

Therefore, the recommended configuration is:

```text
External regulated 5V
       │
       ├──── Servo X VCC
       │
       └──── Servo Y VCC

External GND
       │
       ├──── Servo X GND
       ├──── Servo Y GND
       └──── Arduino GND
```

The Arduino and external servo supply must have a **common ground**.

Servo signal wires remain connected to:

```text
Servo X → D9
Servo Y → D10
```

---

## 🧪 Testing

The project was developed and tested incrementally.

### Stage 1 — Arduino

The Arduino UNO was tested independently.

### Stage 2 — Servo Motor

The servo motor was tested separately to verify movement and signal control.

### Stage 3 — LDR Sensors

The four LDR sensors were tested using the Arduino Serial Monitor.

Example readings:

```text
LDR1: 385
LDR2: 196
LDR3: 115
LDR4: 358
```

The values changed according to the light conditions.

### Stage 4 — Dual-Axis Control

The four LDR sensors were combined with two servo motors to demonstrate horizontal and vertical tracking.

### Stage 5 — IoT

The ESP8266 was configured for Wi-Fi connectivity and ThingSpeak monitoring.

---

## 🛠️ Problems Encountered and Solutions

### 1. ESP8266 COM Port Error

Errors such as:

```text
Could not open port
FileNotFoundError
```

were encountered during ESP8266 programming.

**Solution:** The correct COM port was selected after reconnecting the board and checking the available port in Arduino IDE.

---

### 2. ThingSpeak Library Error

The following compilation error occurred:

```text
fatal error: ThingSpeak.h: No such file or directory
```

**Solution:** The ThingSpeak library was installed through the Arduino Library Manager.

---

### 3. LDR Reading Problem

An LDR initially produced a constant digital HIGH reading during testing.

**Solution:** The LDR was changed to an analog voltage-divider configuration using a 10kΩ resistor and an analog input.

---

### 4. Arduino Reset with Two Servos

When two servos were powered from the Arduino 5V supply, the board showed power/reset issues.

**Solution:** The project was moved toward using an external regulated 5V supply for the servo motors with a common ground shared with the Arduino.

---

## 📁 Repository Structure

```text
IoT-Based-Dual-Axis-Solar-Tracking-System/
│
├── Arduino/
│   └── dual_axis_tracker.ino
│
├── ESP8266/
│   └── thingspeak_iot.ino
│
├── Documentation/
│   └── Solar_Tracking_Project_Report.pdf
│
├── Images/
│   ├── hardware_setup.jpg
│   ├── ldr_setup.jpg
│   └── dual_axis_setup.jpg
│
└── README.md
```

---

## 📷 Project Images

Project photographs are available in the `Images` directory.

They show the hardware setup, LDR circuit, Arduino configuration, and prototype development.

---

## 🚀 Future Scope

The current prototype can be further improved by adding:

* Actual solar panel integration
* Voltage and current sensors
* Measurement of generated electrical power
* Comparison between fixed and tracking panels
* Battery charging system
* Weather sensors
* Mobile/web dashboard
* Automatic night-time repositioning
* More stable tracking algorithms
* MPPT integration
* Data logging and long-term performance analysis

A particularly useful next step would be to measure the electrical output of a fixed panel and compare it with the output obtained using the tracking system.

---

## 🎓 Key Learning Outcomes

Through this project, the following concepts were implemented:

* Embedded systems
* Arduino programming
* Analog sensor interfacing
* Voltage-divider circuits
* Servo motor control
* Dual-axis control
* Serial communication
* ESP8266 Wi-Fi communication
* IoT data monitoring
* ThingSpeak integration
* Hardware troubleshooting
* External power management

---

## 👨‍💻 Technologies Used

* **Arduino C/C++**
* **Arduino UNO**
* **ESP8266 NodeMCU**
* **LDR Sensors**
* **Servo Motors**
* **ThingSpeak**
* **Wi-Fi / IoT**
* **Arduino IDE**

---

## 📄 Documentation

The detailed project report is available in:

```text
Documentation/Solar_Tracking_Project_Report.pdf
```

---

## 👥 Project

This repository contains the implementation and documentation of an academic final-year project:

**IoT-Based Dual-Axis Solar Tracking System**

The project combines embedded control, sensor-based tracking, motor control, and IoT monitoring into a single prototype.
