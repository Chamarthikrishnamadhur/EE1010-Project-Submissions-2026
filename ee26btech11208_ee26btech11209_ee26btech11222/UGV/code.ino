#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE
#include <DabbleESP32.h>

// Motor A (Left Motor)
const int motorA1 = 25;
const int motorA2 = 33;
const int enableA = 14; // Speed control pin

// Motor B (Right Motor)
const int motorB1 = 27;
const int motorB2 = 26; // Fixed: GPIO 36 is input-only
const int enableB = 13; // Speed control pin

// PWM properties (3.0+ syntax)
const int freq = 30000;
const int resolution = 8; 
int dutyCycle = 200;      // Default starting speed (range: 0 to 255)

void setup() {
  Serial.begin(115200);
  
  // Initialize Dabble Bluetooth BLE with device name
  Dabble.begin("ESP32_Robot_Car"); 

  // Initialize motor control direction pins as outputs
  pinMode(motorA1, OUTPUT);
  pinMode(motorA2, OUTPUT);
  pinMode(motorB1, OUTPUT);
  pinMode(motorB2, OUTPUT);
  
  // New ESP32 3.0+ PWM setup
  ledcAttach(enableA, freq, resolution);
  ledcAttach(enableB, freq, resolution);
}

void moveForward() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  ledcWrite(enableA, dutyCycle);
  ledcWrite(enableB, dutyCycle);
}

void moveBackward() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  ledcWrite(enableA, dutyCycle);
  ledcWrite(enableB, dutyCycle);
}

void turnLeft() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, HIGH);
  digitalWrite(motorB1, HIGH);
  digitalWrite(motorB2, LOW);
  ledcWrite(enableA, dutyCycle);
  ledcWrite(enableB, dutyCycle);
}

void turnRight() {
  digitalWrite(motorA1, HIGH);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, HIGH);
  ledcWrite(enableA, dutyCycle);
  ledcWrite(enableB, dutyCycle);
}

void stopCar() {
  digitalWrite(motorA1, LOW);
  digitalWrite(motorA2, LOW);
  digitalWrite(motorB1, LOW);
  digitalWrite(motorB2, LOW);
  ledcWrite(enableA, 0);
  ledcWrite(enableB, 0);
}

void loop() {
  Dabble.processInput(); // Refreshes the smartphone inputs

  // Speed Control via Gamepad Shape Buttons
  if (GamePad.isTrianglePressed()) {
    dutyCycle += 5;
    if (dutyCycle > 255) dutyCycle = 255; // Cap at max speed
    Serial.print("Speed Up: ");
    Serial.println(dutyCycle);
    delay(100); // Small debounce delay
  }
  
  if (GamePad.isCrossPressed()) {
    dutyCycle -= 5;
    if (dutyCycle < 100) dutyCycle = 100; // Floor to prevent motor stall
    Serial.print("Speed Down: ");
    Serial.println(dutyCycle);
    delay(100); // Small debounce delay
  }

  // Directional Movement
  if (GamePad.isUpPressed()) {
    moveForward();
    Serial.println("FWD");
  } 
  else if (GamePad.isDownPressed()) {
    moveBackward();
    Serial.println("BCK");
  } 
  else if (GamePad.isLeftPressed()) {
    turnLeft();
    Serial.println("LFT");
  } 
  else if (GamePad.isRightPressed()) {
    turnRight();
    Serial.println("RHT");
  } 
  else {
    stopCar();
    Serial.println("STP");
  }
}
