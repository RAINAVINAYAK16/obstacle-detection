# 🚗 Obstacle Detection and Accident Prevention System

A simple Arduino-based autonomous vehicle system that detects obstacles using an ultrasonic sensor and prevents collisions by automatically adjusting motor behavior. The system is enhanced with LED indicators for status signaling and a Bluetooth module for manual override via smartphone control.

---

## 📌 Features

- 🧠 **Autonomous Obstacle Detection** using HC-SR04 Ultrasonic Sensor  
- ⚙️ **Motor Speed & Direction Control** via L298N Dual H-Bridge Motor Driver  
- 🔴🔵 **LED Indicators** for Safe and Braking Modes  
- 📱 **Bluetooth Manual Control** using the HC-05 module  
- 🔁 **Real-Time Monitoring & Response** with seamless auto-resume after obstacle clearance

---

## 🛠️ Hardware Requirements

| Component                | Description                                       |
|--------------------------|---------------------------------------------------|
| Arduino Uno              | Main controller for processing logic             |
| HC-SR04 Ultrasonic Sensor| Measures distance to obstacles                   |
| L298N Motor Driver       | Controls direction and speed of DC motors        |
| DC Motors (x2)           | Enables movement of the vehicle                  |
| LEDs (Red & Blue)        | Visual indicators (Safe / Braking)               |
| 330Ω Resistors (x2)      | For current-limiting LEDs                        |
| HC-05 Bluetooth Module   | Enables wireless control from smartphone         |
| Power Supply (12V Battery)| Powers motors and Arduino                       |
| Breadboard & Jumper Wires| Circuit connections                              |

---

## 💻 Software Requirements

- **Arduino IDE**
- **HC-05 Bluetooth Terminal App** (e.g., Serial Bluetooth Terminal for Android)
- Optional: Serial Monitor for debugging

---

## 📐 System Design

The system operates in two modes:
- **Autonomous Mode**:
  - If distance > 15 cm: Vehicle moves forward, blue LED ON
  - If distance ≤ 15 cm: Vehicle stops, red LED ON
- **Bluetooth Manual Mode**:
  - 'F': Move Forward  
  - 'B': Move Backward  
  - 'A': Turn Left  
  - 'D': Turn Right  
  - 'S': Stop  
  - 'R': Resume Auto Mode  

---

## 🧠 How It Works

1. **Start the system** and initialize all components.
2. **Measure distance** from obstacles using the ultrasonic sensor.
3. **Compare** measured distance:
   - ➕ More than 15 cm → Safe → Move Forward
   - ➖ 15 cm or less → Stop Immediately
4. **Control LEDs** and motor behavior based on logic.
5. **Override** anytime via Bluetooth to control movement manually.
6. **Resume automatic behavior** when manual control is released.

---

## 🧾 Code Snippet

```cpp
if (distance > 15) {
  moveForward(255);
  digitalWrite(blueLED, HIGH);
  digitalWrite(redLED, LOW);
} else {
  stopMotors();
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, HIGH);
}
```

---

## ✅ Results

- Accurate real-time detection of obstacles.
- Immediate stop mechanism when within danger range.
- Smooth transition between auto and manual modes.
- Reliable Bluetooth control and quick response.

---

## 🚀 Future Improvements

- 📲 Mobile app interface for better Bluetooth UI
- 🔔 Real-time alerts or data logging via IoT integration
- 🚘 Vehicle-to-Vehicle (V2V) communication to share obstacle data

---

## 📚 References

- Arduino Official Docs – [https://www.arduino.cc](https://www.arduino.cc)  
- HC-SR04 Datasheet  
- L298N Motor Driver Reference  
- HC-05 Bluetooth Module Setup Guides  

---

## 📎 License

This project is open-source and available under the [MIT License](LICENSE).
