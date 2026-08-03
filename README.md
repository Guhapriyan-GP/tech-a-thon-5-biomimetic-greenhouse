# Biomimetic Edge-AI Greenhouse Climate Controller

> **Replacing reactive threshold controllers with predictive, phase-anticipatory hardware.**

## Abstract
Standard greenhouse HVAC systems are reactive, triggering heavy grid-tied exhaust fans only *after* a thermal threshold is breached. This project introduces a closed-loop, edge-AI controller inspired by biological circadian rhythms and plant stomata. By treating environmental telemetry as a continuous periodic signal, the system uses a dual-core DSP/Control architecture to anticipate thermal spikes, verify natural draft actuation physically, and isolate heavy grid loads behind a true hardware failsafe.

## System Architecture

The firmware utilizes a strict separation of concerns via FreeRTOS on an ESP32:

*   **Core 0 (DSP & AI):** Dedicated to a Goertzel-based Discrete-Time Fourier Transform (DTFT) pipeline and an Extreme Learning Machine (ELM). It extracts the phase and magnitude of 24h/12h thermal harmonics to predict heat spikes up to 90 minutes in advance.
*   **Core 1 (Actuation & Telemetry):** Handles the MPU6050 sensor fusion for mechanical vent verification, hardware failsafe gating, and byte-packed MQTT telemetry.

## Key Innovations

### 1. Spectral-Biomimetic AI Pipeline
Instead of relying on simple linear regression, the system tracks cyclical features. We utilize the rate of change of CO2 (dCO2/dt) as a biological cross-signal cue (analogous to stomatal CO2-sensing) to trigger pre-emptive natural ventilation before the thermal mass overheats.

### 2. MPU6050 Closed-Loop Verification
Standard DIY controllers rely on open-loop actuation (assuming a vent opened). We mount an MPU6050 accelerometer/gyroscope directly to the vent flap to:
1.  **Confirm Angle:** The accelerometer proves actual pitch relative to gravity.
2.  **Detect Wind Force:** Gyroscope transients identify natural wind gusts, allowing the controller to reduce stepper motor torque and let natural drafts do the work.

### 3. Galvanically Isolated Hardware Interlock
The grid-tied exhaust fan (Tier 2 fallback) is protected by an industrial-grade hardware failsafe, mirroring ATS logic. The MCU's enable line must pass through a 74LS08 AND gate tied to a hardware watchdog and an optocoupler grid-presence sensor.

### 4. ROI Telemetry (Grid Power Avoided)
To prove efficiency, the system runs a "shadow baseline" (a simulated standard threshold controller) in parallel. The MQTT payload transmits real-time Grid Power Avoided (W), dynamically proving the exact Watt-hours saved by the biomimetic loop.