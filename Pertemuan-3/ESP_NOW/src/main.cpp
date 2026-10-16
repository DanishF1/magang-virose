#include <Arduino.h>
#define led 2

void setup() {
 Serial.begin(9600);
 pinMode(led, OUTPUT);
 digitalWrite(led, HIGH);
}

void loop() {
}
