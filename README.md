# 🛞 Line-Follower Robot — PID Edition

![Platform](https://img.shields.io/badge/platform-Arduino-00979D?style=flat-square&logo=arduino&logoColor=white)
![Language](https://img.shields.io/badge/language-Arduino%20C-A8B9CC?style=flat-square&logo=c&logoColor=black)
![License](https://img.shields.io/badge/license-MIT-00f5ff?style=flat-square)
![Status](https://img.shields.io/badge/status-WIP-orange?style=flat-square)

An autonomous robot that follows a black line on a white surface using an
infrared sensor array and a **PID control loop**. Built, wired and tuned
entirely by hand — from the chassis up to the last line of firmware.

---

## 📷 Demo

<!-- Upload your photos/videos to a /media folder and link them here -->
<!-- ![Robot on track](media/robot-on-track.jpg)                     -->
<!-- ![Top view wiring](media/top-view.jpg)                          -->

| Photo | Video |
|-------|-------|
| `media/robot-on-track.jpg` *(add later)* | `media/demo.mp4` *(add later)* |

---

## 🧠 How It Works

1. **Sense** — a 5-channel IR reflectance array reads how dark the surface
   is under each sensor, producing an error value from -2000 to +2000 that
   describes how far the robot has drifted off the line.
2. **Decide** — a PID controller converts that error into a steering
   correction: `correction = Kp·e + Ki·∫e + Kd·Δe`.
3. **Act** — two DC motors receive PWM signals. The inner wheel slows down
   and the outer wheel speeds up, snapping the robot back onto the line.

The derivative term is what keeps the robot stable at high speed — without
it the robot oscillates left and right around the line.

---

## 🔧 Hardware (BOM)

| Component | Qty | Notes |
|-----------|-----|-------|
| Arduino UNO / Nano | 1 | ATmega328P, 16 MHz |
| TCRT5000 IR sensor array (5ch) | 1 | Line detection |
| L298N motor driver | 1 | Dual H-bridge |
| N20 / TT DC gear motors | 2 | 6V, ~200 RPM |
| Li-ion battery pack (7.4V) | 1 | With switch |
| Chassis + wheels + caster | 1 | 3D printed or acrylic |

Full list with prices: [`docs/BOM.md`](docs/BOM.md)

---

## ⚙️ Tuning Guide

| Parameter | Default | Effect |
|-----------|---------|--------|
| `KP` | 35 | Higher = stronger reaction, may oscillate |
| `KD` | 120 | Higher = smoother, calmer turns |
| `KI` | 0 | Only needed for long gentle curves |
| `BASE_SPEED` | 160 | Raise after the robot is stable |

**Tune in this order:** `KP` until it follows (even if shaky) → `KD` until
the shake disappears → raise `BASE_SPEED` → repeat.

---

## 📂 Repository Structure

```
line-follower-robot/
├── firmware/
│   └── line_follower/
│       └── line_follower.ino    ← main firmware (open with Arduino IDE)
├── docs/
│   ├── BOM.md                   ← parts list
│   └── wiring.md                ← wiring table (add later)
├── media/                       ← photos & videos of the robot
└── README.md
```

---

## 🚀 Getting Started

1. Clone the repo:
   ```bash
   git clone https://github.com/ammmmmamdjh-prog/line-follower-robot.git
   ```
2. Open `firmware/line_follower/line_follower.ino` in the **Arduino IDE**.
3. Select your board and port, then click **Upload**.
4. Place the robot on the track and power it on.

---

## 🗺️ Roadmap

- [x] Basic line following
- [x] PID controller
- [ ] Speed ramps on straights
- [ ] 90° turn detection
- [ ] Bluetooth telemetry

---

## 📄 License

Released under the [MIT License](LICENSE) — © 2026 AmirAli
