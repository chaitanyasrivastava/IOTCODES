#include <Wire.h>
#include <Adafruit_MLX90614.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

// Wi-Fi credentials
const char* ssid = "Chaitanya";
const char* password = "chaitanya";

// Firebase details
#define FIREBASE_HOST "https://animalhealthcare-4eac5-default-rtdb.firebaseio.com/"  // Your Firebase Database URL
#define FIREBASE_AUTH "AIzaSyDXti8V8uLhAacKjEAtlqwrM-QUojvx87o"  // Your Firebase Database Secret

// Firebase data object
FirebaseData firebaseData;

// Create an instance of the MLX90614 sensor
Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
  // Start the serial communication
  Serial.begin(115200);

  // Initialize MLX90614 sensor
  if (!mlx.begin()) {
    Serial.println("Error connecting to MLX90614 sensor. Check wiring.");
    while (1);
  }

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("Connected to Wi-Fi");

  // Initialize Firebase connection
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  Serial.println("Firebase connection established");
}

void loop() {
  // Read ambient and human body temperature from MLX90614
  float ambientTemp = mlx.readAmbientTempC();
  float humanBodyTemp = mlx.readObjectTempC();  // Rename objectTemp to humanBodyTemp for clarity
  
  // Simulate dummy ECG data (for example, normal values could range from 60 to 100)
  int ecgData = random(60, 100);  // Replace with actual ECG sensor data if available
  String ecgStatus = (ecgData >= 60 && ecgData <= 100) ? "Normal" : "Abnormal";

  // Print the readings to the Serial Monitor
  Serial.print("Ambient Temperature: ");
  Serial.print(ambientTemp);
  Serial.println(" °C");
  
  Serial.print("Human Body Temperature: ");
  Serial.print(humanBodyTemp);
  Serial.println(" °C");

  Serial.print("ECG Data: ");
  Serial.print(ecgData);
  Serial.print(" (");
  Serial.print(ecgStatus);
  Serial.println(")");

  // Send ambient and human body temperature data to Firebase
  if (Firebase.setFloat(firebaseData, "/ambientTemperature", ambientTemp)) {
    Serial.println("Ambient temperature updated in Firebase");
  } else {
    Serial.println("Failed to update ambient temperature");
  }

  if (Firebase.setFloat(firebaseData, "/humanBodyTemperature", humanBodyTemp)) {
    Serial.println("Human body temperature updated in Firebase");
  } else {
    Serial.println("Failed to update human body temperature");
  }

  // Send ECG data to Firebase
  if (Firebase.setInt(firebaseData, "/ecgData", ecgData)) {
    Serial.println("ECG data updated in Firebase");
  } else {
    Serial.println("Failed to update ECG data");
  }

  if (Firebase.setString(firebaseData, "/ecgStatus", ecgStatus)) {
    Serial.println("ECG status updated in Firebase");
  } else {
    Serial.println("Failed to update ECG status");
  }

  // Wait for 2 seconds before the next reading
  delay(2000);
}
