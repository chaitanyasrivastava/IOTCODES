#include <AFMotor.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


#define Speed 180

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
int data [2];
RF24 radio(23, 22);  // NRF24L01 module connections (CE, CSN)
const uint64_t pipe = 0xE8E8F0F0E1LL;  // Pipe address for communication

void setup() {
  Serial.begin(9600);
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);

  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(data, sizeof(data));

    int X = map(data[0], 0, 1023, 0, 1023);
    int Y = map(data[0], 0, 1023, 0, 1023);

    Serial.print(X);
    Serial.print("\t");
    Serial.println(Y);

    if (X >= 800) {
      motor1.run(BACKWARD);
      motor2.run(BACKWARD);
    } else if (X <= 200) {
      motor1.run(FORWARD);
      motor2.run(FORWARD);
    } else if (Y >= 800) {
      motor1.run(FORWARD);
      motor2.run(BACKWARD);
    } else if (Y <= 200) {
      motor1.run(BACKWARD);
      motor2.run(FORWARD);
    } else {
      motor1.run(RELEASE);
      motor2.run(RELEASE);
    }
  }
}