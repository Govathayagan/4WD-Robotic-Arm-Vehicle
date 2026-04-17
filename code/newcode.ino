#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "BluetoothSerial.h"

// Bluetooth
BluetoothSerial SerialBT;

// Servo driver setup
Adafruit_PWMServoDriver pwm;
#define SERVO_FREQ 60 // Standard 60Hz for servos
int servo1 = 90;
int servo2 = 110;
int servo3 = 40;
int servo4 = 50;
int servo5 = 90;

// Motor control pins for L298
#define enA 5  // Enable1 L298 Pin enA 
#define in1 33 // Motor1 L298 Pin in1 
#define in2 32 // Motor1 L298 Pin in2 
#define in3 25 // Motor2 L298 Pin in3 
#define in4 26 // Motor2 L298 Pin in4 
#define enB 18 // Enable2 L298 Pin enB 

int bt_data;
int Speed = 130;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("ESP32_Robot");  // Set Bluetooth device name

  // Initialize PCA9685
  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ); // Set PWM frequency for servos

  // Set motor control pins
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(enB, OUTPUT);

  delay(1000);
}

void loop() {
  if (SerialBT.available() > 0) {
    bt_data = SerialBT.read();
    Serial.println(bt_data);
    if (bt_data > 20) {
      Speed = bt_data;
    }
  }

  analogWrite(enA, Speed);
  analogWrite(enB, Speed);

  if (bt_data == 1) {
    forward();
  } else if (bt_data == 2) {
    backward();
  } else if (bt_data == 3) {
    turnLeft();
  } else if (bt_data == 4) {
    turnRight();
  } else if (bt_data == 5) {
    Stop();
  } else if (bt_data == 6) {
    turnLeft(); delay(400); bt_data = 5;
  } else if (bt_data == 7) {
    turnRight(); delay(400); bt_data = 5;
  } else if (bt_data == 8) {
    if (servo1 < 180) servo1++;
    pwm.setPWM(0, 0, map(servo1, 0, 180, 0, 4095)); // Servo 1
  } else if (bt_data == 9) {
    if (servo1 > 0) servo1--;
    pwm.setPWM(0, 0, map(servo1, 0, 180, 0, 4095)); // Servo 1
  } else if (bt_data == 10) {
    if (servo2 > 0) servo2--;
    pwm.setPWM(1, 0, map(servo2, 0, 180, 0, 4095)); // Servo 2
  } else if (bt_data == 11) {
    if (servo2 < 180) servo2++;
    pwm.setPWM(1, 0, map(servo2, 0, 180, 0, 4095)); // Servo 2
  } else if (bt_data == 12) {
    if (servo3 > 0) servo3--;
    pwm.setPWM(2, 0, map(servo3, 0, 180, 0, 4095)); // Servo 3
  } else if (bt_data == 13) {
    if (servo3 < 180) servo3++;
    pwm.setPWM(2, 0, map(servo3, 0, 180, 0, 4095)); // Servo 3
  } else if (bt_data == 14) {
    if (servo4 < 180) servo4++;
    pwm.setPWM(3, 0, map(servo4, 0, 180, 0, 4095)); // Servo 4
  } else if (bt_data == 15) {
    if (servo4 > 0) servo4--;
    pwm.setPWM(3, 0, map(servo4, 0, 180, 0, 4095)); // Servo 4
  } else if (bt_data == 16) {
    if (servo5 > 90) servo5--;
    pwm.setPWM(4, 0, map(servo5, 0, 180, 0, 4095)); // Servo 5
  } else if (bt_data == 17) {
    if (servo5 < 150) servo5++;
    pwm.setPWM(4, 0, map(servo5, 0, 180, 0, 4095)); // Servo 5
  }

  delay(30);
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void turnRight() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void turnLeft() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void Stop() {
    digitalWrite(in2, LOW);
    digitalWrite(in1, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

 
