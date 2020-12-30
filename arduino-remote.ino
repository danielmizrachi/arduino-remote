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
  digitalWrite(pins[pin_id], states[pin_id]);
}

void setup() {
  Serial.begin(BAUD);
  
  pins[0] = PIN4;
  pins[1] = PIN3;
  pins[2] = PIN2;

  for (int i = 0; i < PIN_COUNT; i++) {
    pinMode(pins[i], OUTPUT);
  }

  // Confirm ready by sending one byte
  Serial.print('a');
}

void loop() {
  int input, pin_id;

  if (Serial.available() > 0) {
    input = Serial.read();
    
    pin_id = input % PIN_COUNT;
    toggle(pin_id);
  }
}
