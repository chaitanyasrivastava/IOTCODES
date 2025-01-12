#include <SoftwareSerial.h>

// Define motor control pins
const int motorAPin1 = 2;
const int motorAPin2 = 3;
const int motorBPin1 = 4;
const int motorBPin2 = 5;

const int enableAPin = 9;
const int enableBPin = 10;

// Define Bluetooth module pins
const int bluetoothTxPin = 0;
const int bluetoothRxPin = 1;

// Create a SoftwareSerial object for Bluetooth communication
SoftwareSerial bluetoothSerial(bluetoothTxPin, bluetoothRxPin);

void setup() {
  pinMode(motorAPin1, OUTPUT);
  pinMode(motorAPin2, OUTPUT);
  pinMode(motorBPin1, OUTPUT);
  pinMode(motorBPin2, OUTPUT);
  pinMode(enableAPin, OUTPUT);
  pinMode(enableBPin, OUTPUT);

  // Set the baud rate for Bluetooth communication
  bluetoothSerial.begin(9600);
}

void loop() {
  if (bluetoothSerial.available() > 0) {
    char command = bluetoothSerial.read();

    // Forward
    if (command == 'F') {
      digitalWrite(motorAPin1, HIGH);
      digitalWrite(motorAPin2, LOW);
      analogWrite(enableAPin, 255);

      digitalWrite(motorBPin1, HIGH);
      digitalWrite(motorBPin2, LOW);
      analogWrite(enableBPin, 255);
    }
    // Backward
    else if (command == 'B') {
      digitalWrite(motorAPin1, LOW);
      digitalWrite(motorAPin2, HIGH);
      analogWrite(enableAPin, 255);

      digitalWrite(motorBPin1, LOW);
      digitalWrite(motorBPin2, HIGH);
      analogWrite(enableBPin, 255);
    }
    // Left
    else if (command == 'L') {
      digitalWrite(motorAPin1, LOW);
      digitalWrite(motorAPin2, HIGH);
      analogWrite(enableAPin, 200);

      digitalWrite(motorBPin1, HIGH);
      digitalWrite(motorBPin2, LOW);
      analogWrite(enableBPin, 200);
    }
    // Right
    else if (command == 'R') {
      digitalWrite(motorAPin1, HIGH);
      digitalWrite(motorAPin2, LOW);
      analogWrite(enableAPin, 200);

      digitalWrite(motorBPin1, LOW);
      digitalWrite(motorBPin2, HIGH);
      analogWrite(enableBPin, 200);
    }
    // Stop
    else if (command == 'S') {
      digitalWrite(motorAPin1, LOW);
      digitalWrite(motorAPin2, LOW);
      digitalWrite(motorBPin1, LOW);
      digitalWrite(motorBPin2, LOW);
      analogWrite(enableAPin, 0);
      analogWrite(enableBPin, 0);
    }
  }
}
