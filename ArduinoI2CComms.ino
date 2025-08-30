// Controller Reader

#include <Wire.h>
#include "TemperatureReader.ino" // Some way to turn on the fans, ok the problem is that the code makes it so that all of the fans turn on at the same time
const int elbowPin = 2;
const int shoulderPin = 4;
const int wrist1Pin = 7;
const int wrist2Pin = 8;
void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(elbowPin, OUTPUT);
  pinMode(shoulderPin, OUTPUT);
  pinMode(wrist1Pin, OUTPUT);
  pinMode(wrist2Pin, OUTPUT);
}

void loop() {
  // Idk which peripheral we're writing it to
  Wire.requestFrom(8, 6);

  // If the wire is available, read the bits and then turn on fan based on the binary data
  if (Wire.available()){
    const int tempBinary = Wire.read()
    // (Wrist2)(Wrist1)(Shoulder)(Elbow)
    // 0b0001 = Elbow temp
    if (tempBinary & 0b00000001 == 0b00000001){
      // Turn on elbow fan, oh shoot wait
      Serial.println("Turning on elbow fan");
      digitalWrite(elbowPin, HIGH);
    }
    else {
      // Turn off elbow fan
      Serial.println("Turning off elbow fan");
      digitalWrite(elbowPin, LOW);
    }

    // 0b0010 = Shoulder temp
    if (tempBinary & 0b00000010 == 0b00000010){
      // Turn on shoulder fan
      Serial.println("Turning on shoulder fan");
      digitalWrite(shoulderPin, HIGH);
    }
    else {
      // Turn off shoulder fan
      Serial.println("Turning off shoulder fan");
      digitalWrite(shoulderPin, LOW);
    }

    // 0b0100 = Wrist1 temp
    if (tempBinary & 0b00000100 == 0b00000100){
      // Turn on wrist1 fan
      Serial.println("Turning on wrist1 fan");
      digitalWrite(wrist1Pin, HIGH);
    }
    else {
      // Turn off wrist1 fan
      Serial.println("Turning off wrist1 fan");
      digitalWrite(wrist1Pin, LOW);
    }

    // 0b1000 = Wrist2 temp
    if (tempBinary & 0b00001000 == 0b00001000){
      // Turn on wrist2 fan
      Serial.println("Turning on wrist2 fan");
      digitalWrite(wrist2Pin, HIGH);
    }
    else {
      // Turn off wrist2 fan
      Serial.println("Turning off wrist2 fan");
      digitalWrite(wrist2Pin, LOW);
    }
  }
}
