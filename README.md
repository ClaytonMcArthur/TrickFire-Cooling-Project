# TrickFire Cooling System — Orin Fan Controller

A compact cooling controller for TrickFire Robotics. The project combines a custom **KiCad PCB**, an **Arduino Nano Every** for control, and an **I²C Python host** on an NVIDIA Jetson (**Orin/Nano**) to read temperature and drive multiple 5 V fans with PWM/low‑side switching.

---

## 📦 What’s in this repo

- `Trickfire Cooling System - Control PCB.kicad_sch` — Schematic (KiCad)
- `Trickfire Cooling System - Control PCB.kicad_pcb` — Board layout (KiCad)
- `ArduinoI2CComms.ino` — Arduino I²C firmware (slave device; fan control & telemetry)
- `TemperatureReader.ino` / `TemperatureReaderPWM.ino` / `Test1TempSensorTrickFire.ino` — Sensor/PWM test sketches
- `coolingI2C.py` — Host‑side Python tool to talk to the Arduino over I²C
- `PCB.png` — Render of the board
- `Schematic.png` — High‑level wiring diagram

> Note: The I²C address/command map live in `ArduinoI2CComms.ino` (kept generic here).

---

## 🛠️ Hardware overview

- **MCU**: Arduino **Nano Every**
- **Power**: 12 V input → 5 V buck (module shown: **LY‑KREE XS120503**)
- **Fan channels**: 4× low‑side NMOS drivers (e.g., **RFP30N06LE**) for 5 V brushless fans
- **Headers**: I²C (SCL/SDA), UART (RX1/TX1), additional GPIO
- **Stacks/planes**: solid GND pours, star power from buck to fans & MCU

### Connectors (silkscreen labels)
- **J11**: I²C **SCL/SDA**
- **J12**: **RX1/TX1** (UART to Orin / debug)
- **J5–J8**: Fan outputs (per‑channel NMOS)
- **J13**: Power entry / buck input (12 V)  
  *See schematic for exact pinouts.*

---

## 🔌 System architecture

1. **Jetson Orin/Nano** runs `coolingI2C.py` to send I²C commands (target setpoints / manual duty) and read temperatures/telemetry.
2. **Arduino Nano Every** (I²C slave) interprets commands and outputs PWM to the MOSFET gates for each fan channel.
3. **Control PCB** provides power distribution and MOSFET low‑side switching for the 5 V fans.

PCB:
![PCB](PCB.png)
Schematic:
![Schematic](Schematic.png)

---

## 🚀 Getting started

### 1) Hardware
- Feed **12 V** into the buck module; verify **5 V** at the fan rail and MCU.
- Connect fans to **J5–J8** (observe polarity). Keep total current within buck/MOSFET limits.
- Connect Orin/Nano I²C to **J11** (SCL/SDA) and common **GND**; optional UART via **J12**.

### 2) Firmware (Arduino)
- Open `ArduinoI2CComms.ino`, select **Arduino Nano Every**, and upload.
- Confirm the I²C address and any register/command IDs defined in the sketch.

### 3) Host (Python on Jetson)
```bash
sudo apt-get install -y python3-smbus i2c-tools
# Enable I²C in Jetson config if not already enabled
python3 coolingI2C.py -h   # view options/usage
```
- Typical flows:
  - **Manual**: set duty on one or more fan channels.
  - **Closed‑loop**: use `TemperatureReader*.ino` to read a sensor and map temperature → PWM.

---

## 🧪 Testing ideas
- Verify gate signals with a scope while sweeping duty.
- Spin up one channel at a time; monitor 5 V rail sag.
- Exercise thermal control by heating/cooling the sensor and watching duty track the setpoint.

---

## ⚠️ Safety & limits
- Size the buck regulator for **sum of fan currents + MCU margin**.
- Provide airflow and copper for MOSFET dissipation; keep traces short for gate loops.
- Add fusing on the 12 V input in the final build.

---

## 📁 Repo layout (suggested)
```
/firmware/        # Arduino sketches
/host/            # Python I²C tool + helpers
/hardware/        # KiCad files, images, exports
README.md
```

## 🙌 Acknowledgments
TrickFire Robotics contributors and reviewers.
