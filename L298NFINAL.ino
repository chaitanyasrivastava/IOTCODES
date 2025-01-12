#include <SPI.h>
#include "RF24.h"

const int motorforward = A1;
const int motorbackward = A2;
const int motorleft = A3;
const int motorright = A4;

int data[2];
RF24 radio(9, 8); // CE, CSN
const uint64_t pipe = 0xE8E8F0F0E1LL;

void setup() {
  pinMode(motorforward, OUTPUT);
  pinMode(motorbackward, OUTPUT);
  pinMode(motorleft, OUTPUT);
  pinMode(motorright, OUTPUT);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&data, sizeof(data));
    int xvalue = data[0];
    int yvalue = data[1];

    // Control the motors based on received values
    if (yvalue > 1 && yvalue < 51) {
      digitalWrite(motorforward, HIGH);
      digitalWrite(motorbackward, HIGH);
    } else if (yvalue > 77 && yvalue < 128) {
      digitalWrite(motorforward, LOW);
      digitalWrite(motorbackward, LOW);
    } else {
      digitalWrite(motorforward, LOW);
      digitalWrite(motorbackward, LOW);
    }

    if (xvalue > 129 && xvalue < 179) {
      digitalWrite(motorleft, HIGH);
      digitalWrite(motorright, LOW);
    } else if (xvalue > 205 && xvalue < 255) {
      digitalWrite(motorleft, LOW);
      digitalWrite(motorright, HIGH);
    } else {
      digitalWrite(motorleft, LOW);
      digitalWrite(motorright, LOW);
    }

    Serial.print("Received X-axis: ");
    Serial.print(xvalue);
    Serial.print("\tReceived Y-axis: ");
    Serial.println(yvalue);
  }
}