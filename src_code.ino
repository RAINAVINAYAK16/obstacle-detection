#include <SoftwareSerial.h>

// Ultrasonic Sensor Pins
const int trigPin = 9;
const int echoPin = 7;

// Motor A (Left Motor)
const int motorA_IN1 = 10;
const int motorA_IN2 = 11;
const int motorA_ENA = 3; // PWM Speed Control

// Motor B (Right Motor)
const int motorB_IN3 = 8;
const int motorB_IN4 = 12;
const int motorB_ENB = 5; // PWM Speed Control

// LED Pins
const int blueLED = A5;  // Blue LED for slowing down
const int redLED = A1;   // Red LED for halt

// Bluetooth Serial on pins 2 (RX) and 4 (TX)
SoftwareSerial BT(2, 4);

bool bluetoothOverride = false;
char btCommand = ' ';

void setup() {
  Serial.begin(115200);
  BT.begin(9600); // HC-05 default

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(motorA_IN1, OUTPUT);
  pinMode(motorA_IN2, OUTPUT);
  pinMode(motorA_ENA, OUTPUT);

  pinMode(motorB_IN3, OUTPUT);
  pinMode(motorB_IN4, OUTPUT);
  pinMode(motorB_ENB, OUTPUT);

  pinMode(blueLED, OUTPUT);
  pinMode(redLED, OUTPUT);

  moveForward(255);
}

void loop() {
  // Check Bluetooth input
  if (BT.available()) {
    btCommand = BT.read();
    bluetoothOverride = true;
  }

  if (bluetoothOverride) {
    handleBluetoothCommand(btCommand);
  } else {
    autoDrive();
  }

  delay(100);
}

void autoDrive() {
  int distance = getDistance();
  Serial.print("Distance: ");
  Serial.println(distance);

  resetLEDs();

  if (distance > 120) {
    moveForward(255);
    digitalWrite(blueLED, HIGH);
  } else if (distance > 90) {
    moveForward(200);
    digitalWrite(blueLED, HIGH);
  } else if (distance > 70) {
    moveForward(150);
    digitalWrite(blueLED, HIGH);
  } else if (distance > 50) {
    moveForward(100);
    digitalWrite(blueLED, HIGH);
    digitalWrite(blueLED, LOW);
  } else if (distance > 20) {
    moveForward(50);
    digitalWrite(redLED, HIGH);
    digitalWrite(redLED, LOW);
    digitalWrite(redLED, HIGH);
  } else {
    stopMotors();
    digitalWrite(blueLED, LOW);
    digitalWrite(redLED, HIGH);
  }
}

void handleBluetoothCommand(char cmd) {
  resetLEDs();
  switch (cmd) {
    case 'F': moveForward(200); break;
    case 'S': stopMotors(); digitalWrite(redLED, HIGH); break;
    case 'A': moveLeft(200); break;
    case 'D': moveRight(200); break;
    case 'B': moveBackward(200); break;
    case 'R': bluetoothOverride = false; break; // Resume auto mode
    default: stopMotors(); break;
  }
}

int getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  int duration = pulseIn(echoPin, HIGH, 20000); 
  int distance = duration * 0.0343 / 2; 

  return (duration == 0) ? 999 : distance; 
}

void moveForward(int speed) {
  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, HIGH);
  analogWrite(motorA_ENA, speed);

  digitalWrite(motorB_IN3, LOW);
  digitalWrite(motorB_IN4, HIGH);
  analogWrite(motorB_ENB, speed);
}

void moveBackward(int speed) {
  digitalWrite(motorA_IN1, HIGH);
  digitalWrite(motorA_IN2, LOW);
  analogWrite(motorA_ENA, speed);

  digitalWrite(motorB_IN3, HIGH);
  digitalWrite(motorB_IN4, LOW);
  analogWrite(motorB_ENB, speed);
}

void moveLeft(int speed) {
  digitalWrite(motorA_IN1, HIGH);
  digitalWrite(motorA_IN2, LOW);
  analogWrite(motorA_ENA, speed);

  digitalWrite(motorB_IN3, LOW);
  digitalWrite(motorB_IN4, HIGH);
  analogWrite(motorB_ENB, speed);
}

void moveRight(int speed) {
  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, HIGH);
  analogWrite(motorA_ENA, speed);

  digitalWrite(motorB_IN3, HIGH);
  digitalWrite(motorB_IN4, LOW);
  analogWrite(motorB_ENB, speed);
}

void stopMotors() {
  digitalWrite(motorA_IN1, LOW);
  digitalWrite(motorA_IN2, LOW);
  digitalWrite(motorB_IN3, LOW);
  digitalWrite(motorB_IN4, LOW);
  analogWrite(motorA_ENA, 0);
  analogWrite(motorB_ENB, 0);
}

void resetLEDs() {
  digitalWrite(blueLED, LOW);
  digitalWrite(redLED, LOW);
}