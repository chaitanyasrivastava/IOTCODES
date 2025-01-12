#define ECG_SENSOR_PIN A0 // Analog input pin for ECG sensor

void setup() {
  Serial.begin(115200); // Initialize Serial communication
}

void loop() {
  int ecgValue = analogRead(ECG_SENSOR_PIN); // Read the analog value from ECG sensor

  // Output the value to the Serial Plotter
  Serial.print("ECG Value: ");
  Serial.println(ecgValue);

  // Send a newline character to separate values in the Serial Plotter
  Serial.println();

  delay(10); // Optional delay to adjust the reading frequency
}
