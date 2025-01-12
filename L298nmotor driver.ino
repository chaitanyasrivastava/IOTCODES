// Define motor pins
int motorPin1 = 2;  // Connect to IN1 on the L298N
int motorPin2 = 3;  // Connect to IN2 on the L298N
int enablePin = 4;  // Connect to ENA on the L298N

void setup() {
  // Set the motor pins as outputs
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(enablePin, OUTPUT);
}

void loop() {
  // Set the direction and speed of the motor
  digitalWrite(motorPin1, HIGH);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 255);  // Set the speed to maximum (255)

  // Wait for a few seconds to allow the gate to open
  delay(5000);

  // Stop the motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);  // Set the speed to zero

  // Wait for a few seconds before closing the gate
  delay(5000);

  // Set the direction and speed of the motor to close the gate
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, HIGH);
  analogWrite(enablePin, 255);  // Set the speed to maximum (255)

  // Wait for a few seconds to allow the gate to close
  delay(5000);

  // Stop the motor
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
  analogWrite(enablePin, 0);  // Set the speed to zero

  // Wait for a few seconds before repeating the cycle
  delay(5000);
}
