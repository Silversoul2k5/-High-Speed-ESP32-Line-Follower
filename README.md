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

🚀 Key Features
⚡ High-Speed Performance

Runs near maximum PWM (255) on straight sections

Dynamic braking for curves and turns

Optimized for compact competition tracks

🔁 Intelligent Turn Handling

Acute angles (30°–60°) handled smoothly using PID

True 90° turns executed using on-spot pivot
(one wheel forward, the other reverse)

Prevents false pivots on sharp curves

🎯 Advanced Control Logic

PD controller (Kp + Kd) tuned for high speed

No Ki → avoids integral windup

Two-stage turn classification:

Curve vs Pivot

👀 RoboEyes OLED Display

Animated robotic eyes using FluxGarage RoboEyes

Runs independently of motor control (non-blocking)

Adds personality without affecting performance

🧠 No Calibration Required

Fixed threshold logic

Reliable across varying lighting conditions

Faster startup and simpler deployment

