# 🔩 Bill of Materials — Line-Follower Robot

Realistic parts list with rough price ranges (Iran market may vary).

| # | Component | Qty | Spec | Est. Price (USD) |
|---|-----------|-----|------|------------------|
| 1 | Arduino UNO R3 (clone OK) | 1 | ATmega328P | $5 – $8 |
| 2 | TCRT5000 IR array | 1 | 5-channel, digital out | $2 – $4 |
| 3 | L298N motor driver | 1 | Dual H-bridge, 2A | $1.5 – $3 |
| 4 | N20 gear motor | 2 | 6V, 200 RPM, magnetic encoder optional | $3 – $6 /pair |
| 5 | N20 wheel pair | 1 | 65 mm | $2 |
| 6 | Ball caster | 1 | Metal, 12 mm | $1 |
| 7 | Li-ion 18650 × 2 + holder | 1 | 7.4 V nominal | $4 – $6 |
| 8 | Slide switch | 1 | 3A | $0.3 |
| 9 | Chassis (acrylic / 3D print) | 1 | Two-deck recommended | $3 – $8 |
| 10 | Jumper wires, spacers, screws | 1 set | Dupont + M3 | $2 |

**Total: roughly $25 – $40**

## Notes
- Keep the sensor array **2 – 8 mm** above the surface — height is the #1
  cause of bad readings.
- Power the Arduino from the same battery through the driver's 5V regulator,
  or from a separate 9V supply — never from two sources at once.
- Twist the motor wires to reduce electrical noise on the sensor inputs.
