/*
 * Serial receiver controlling pins of an Arduino, built using Uno
 * Copyright (c) 2020 Daniel Mizrachi <mail@danmiz.net>
 */

// Number of pins connected
#define PIN_COUNT 5
#define BAUD 9600

// Pins of connected output devices (presumably LEDs)
uint8_t pins[PIN_COUNT] = { PIN6, PIN5, PIN4, PIN3, PIN2 };

// Cached states of pins to save digitalReads
bool states[PIN_COUNT];

// Toggles physical and cached state of given pin
void toggle(uint8_t pin_id) {
  states[pin_id] = !states[pin_id];
  digitalWrite(pins[pin_id], states[pin_id]);
  Serial.write((uint8_t*)states, PIN_COUNT);
}

void setup() {
  Serial.begin(BAUD);

  for (int i = 0; i < PIN_COUNT; i++) {
    states[i] = false;
    pinMode(pins[i], OUTPUT);
  }

  // Confirm ready by transmitting PIN_COUNT
  Serial.write(PIN_COUNT);
}

void loop() {
  int input, pin_id;

  if (Serial.available() > 0) {
    input = Serial.read();
    
    pin_id = input % PIN_COUNT;
    toggle(pin_id);
  }
}
