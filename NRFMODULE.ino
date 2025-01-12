#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(23, 22); // NRF24L01 module pins

int joystickXPin = A0;  // Joystick X-axis analog pin
int joystickYPin = A1;  // Joystick Y-axis analog pin
int joystickX2Pin = A2; // Joystick X2-axis analog pin
int joystickY2Pin = A3; // Joystick Y2-axis analog pin

int motorStopThreshold = 100; // Threshold to consider as stop signal

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(0xF0F0F0F0E1LL); // Set the transmitting address
}

void loop() {
  int joystickXValue = analogRead(joystickXPin);   // Read X-axis value
  int joystickYValue = analogRead(joystickYPin);   // Read Y-axis value
  int joystickX2Value = analogRead(joystickX2Pin); // Read X2-axis value
  int joystickY2Value = analogRead(joystickY2Pin); // Read Y2-axis value

  // Check if joystick values are within the stop threshold
  if (abs(joystickXValue - 512) < motorStopThreshold &&
      abs(joystickYValue - 512) < motorStopThreshold &&
      abs(joystickX2Value - 512) < motorStopThreshold &&
      abs(joystickY2Value - 512) < motorStopThreshold) {
    // Send stop signal
    int motorSpeeds[4] = {0, 0, 0, 0};
    radio.write(&motorSpeeds, sizeof(motorSpeeds));
  } else {
    // Map the joystick values to motor speeds
    int motorASpeed = map(joystickYValue, 0, 1023, -255, 255);
    int motorBSpeed = map(joystickXValue, 0, 1023, -255, 255);
    int motorCSpeed = map(joystickY2Value, 0, 1023, -255, 255);
    int motorDSpeed = map(joystickX2Value, 0, 1023, -255, 255);

    // Send the motor speeds to the receiver
    int motorSpeeds[4] = {motorASpeed, motorBSpeed, motorCSpeed, motorDSpeed};
    radio.write(&motorSpeeds, sizeof(motorSpeeds));
  }

  delay(100); // Adjust delay as needed
}
