/*
 * Serial receiver controlling pins of an Arduino (built using Uno)
 * Copyright (c) 2020 Daniel Mizrachi <mail@danmiz.net>
 */

#define PIN_COUNT 3
#define BAUD 9600

// Pins of connected output devices (presumably LEDs)
uint8_t pins[PIN_COUNT];
// Cached states of pins to save digitalReads
bool states[PIN_COUNT] = { false, false, false };

// Toggles physical and cached state of given pin
void toggle(uint8_t pin_id) {
  states[pin_id] = !states[pin_id];
  digitalWrite(pins[pin_id], (uint8_t)states[pin_id]);
}

void setup() {
  Serial.begin(BAUD);
  
  pins[0] = PIN4;
  pins[1] = PIN3;
  pins[2] = PIN2;

  for (int i = 0; i < PIN_COUNT; i++) {
    pinMode(pins[i], OUTPUT);
  }
}

void loop() {
  int input, pin_id;

  while (Serial.available() > 0) {
    input = Serial.parseInt();
    
    // Debug
    Serial.print("Got: ");
    Serial.println(input);
    
    // Ignore 0s as these are returned upon timeout
    // Instead we look for >1, subtract and mod to get array index
    if (input >= 1) {
      pin_id = (input - 1) % PIN_COUNT;
      toggle(pin_id);

      // Debug
      delay(100);
      Serial.print("Set: ");
      Serial.println(pin_id);
    }
  }
}
