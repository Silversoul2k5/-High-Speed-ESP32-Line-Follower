# -High-Speed-ESP32-Line-Follower
High-speed ESP32 line follower using an 8-IR sensor array, TB6612FNG motor driver, and PD control. Optimized for compact tracks, it smoothly handles acute curves and executes on-spot 90° pivot turns at near-max speed. Includes RoboEyes OLED for live animated feedback.

A high-performance autonomous line follower robot built using ESP32, 8-channel IR sensor array, and TB6612FNG motor driver, capable of completing a dense, compact, competition-style track in ~30 seconds.

This project focuses on speed, accuracy, and stability, handling:

Acute angles

circle

cross-junction

Tight S-curves

zig-zag

True 90° turns (on-spot pivot)

High-speed straights
___________________________________________________

## 🚀 Key Features

### ⚡ High-Speed Performance

* Runs near **maximum PWM (255)** on straight sections
* Dynamic braking for curves and turns
* Optimized for **compact competition tracks**

### 🔁 Intelligent Turn Handling

* **Acute angles (30°–60°)** handled smoothly using PID
* **True 90° turns** executed using **on-spot pivot**
  (one wheel forward, the other reverse)
* Prevents false pivots on sharp curves

### 🎯 Advanced Control Logic

* **PD controller (Kp + Kd)** tuned for high speed
* No Ki → avoids integral windup
* Two-stage turn classification:

  * Curve vs Pivot

### 👀 RoboEyes OLED Display

* Animated robotic eyes using **FluxGarage RoboEyes**
* Runs independently of motor control (non-blocking)
* Adds personality without affecting performance

### 🧠 No Calibration Required

* Fixed threshold logic
* Reliable across varying lighting conditions
* Faster startup and simpler deployment

---

## 🛠️ Hardware Used

| Component    | Description                           |
| ------------ | ------------------------------------- |
| MCU          | ESP32                                 |
| Sensors      | 8-channel IR reflectance sensor array |
| Motor Driver | TB6612FNG                             |
| Motors       | 6V DC geared motors (N20 class)       |
| Display      | 0.96" OLED SSD1306                    |
| Power        | Li-ion / LiPo (regulated)             |
| Chassis      | Custom compact line follower chassis  |

---


________________________________________________________
# 🔌 Full Hardware Connections
________________________________________________________
## 🧠 ESP32 (Main Controller)

* Board: ESP32 Dev Module / ESP32-WROOM
* Logic Voltage: **3.3 V**
* Motor Power: **External battery (recommended)**

---

## 👁️ 8-Channel IR Sensor Array (Analog)

> **Threshold logic**
> BLACK ≥ 3600
> WHITE < 3600

| IR Sensor | ESP32 Pin    | ESP32 ADC |
| --------- | ------------ | --------- |
| IR1       | GPIO 26      | ADC2      |
| IR2       | GPIO 25      | ADC2      |
| IR3       | GPIO 33      | ADC1      |
| IR4       | GPIO 32      | ADC1      |
| IR5       | GPIO 35      | ADC1      |
| IR6       | GPIO 34      | ADC1      |
| IR7       | GPIO 39 (VN) | ADC1      |
| IR8       | GPIO 36 (VP) | ADC1      |

### IR Power

| IR Pin | Connect To            |
| ------ | --------------------- |
| VCC    | **3.3 V** (preferred) |
| GND    | ESP32 GND             |

⚠️ **Do NOT power IR sensors from 5 V** when using ESP32 ADC.

---

## ⚙️ TB6612FNG Motor Driver

### Left Motor

| TB6612FNG | ESP32   |
| --------- | ------- |
| PWMA      | GPIO 18 |
| AIN1      | GPIO 19 |
| AIN2      | GPIO 21 |

### Right Motor

| TB6612FNG | ESP32   |
| --------- | ------- |
| PWMB      | GPIO 5  |
| BIN1      | GPIO 17 |
| BIN2      | GPIO 16 |

### Control & Power

| TB6612FNG Pin | Connection                |
| ------------- | ------------------------- |
| STBY          | GPIO 23                   |
| VM            | Motor Battery + (6–7.4 V) |
| VCC           | ESP32 **3.3 V**           |
| GND           | Common GND                |
| AO1 / AO2     | Left Motor                |
| BO1 / BO2     | Right Motor               |

⚠️ **Important**

* Motor battery **GND must be common** with ESP32 GND
* Do NOT power motors from ESP32 5V pin
* If you are using external battery the -ve should be give to a differnt ground of TB6612FNG

---

## 👀 OLED Display (SSD1306 – I2C)

| OLED Pin | ESP32 Pin |
| -------- | --------- |
| SDA      | GPIO 4    |
| SCL      | GPIO 22   |
| VCC      | 3.3 V     |
| GND      | GND       |

✔ These pins are chosen to **avoid motor pin conflicts**
✔ Works perfectly with RoboEyes library

---

## 🔋 Power Recommendation (Very Important)

| Component  | Power Source                   |
| ---------- | ------------------------------ |
| ESP32      | Buck / 5 V → onboard regulator |
| IR Sensors | ESP32 3.3 V                    |
| OLED       | ESP32 3.3 V                    |
| Motors     | Separate battery (6–7.4 V)     |
| TB6612 VCC | ESP32 3.3 V                    |

## ☕ Support & Donations

If this project helped you or inspired your build, you can support my work:

- ❤️ GitHub Sponsors
- ☕ Buy Me a Coffee: [CLICK_HERE](https://buymeacoffee.com/silversoul2k5)

Thank you for supporting open-source robotics!



