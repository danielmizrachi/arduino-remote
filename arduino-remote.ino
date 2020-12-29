/*
 * Serial receiver controlling pins of an Arduino (built using Uno)
 * Copyright Daniel Mizrachi 2020 <mail@danmiz.net>
 */

#define PIN_COUNT 3

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
  Serial.begin(9600);
  
  pins[0] = PIN4;
  pins[1] = PIN3;
  pins[2] = PIN2;

  for (int i = 0; i < PIN_COUNT; i++) {
    pinMode(pins[i], OUTPUT);
    toggle(i);
  }

  delay(500);

  toggle(0);
  toggle(1);
  toggle(2);
}

void loop() {
  int input, pin_id;

  while (Serial.available() > 0) {
    input = Serial.parseInt();
    Serial.print("Got: ");
    Serial.println(input);

    // Device appears to receive a 0 following each input
    // so we look for >1, subtract and mod for array index
    if (input >= 1) {
      pin_id = (input - 1) % PIN_COUNT;
      Serial.print("Set: ");
      Serial.println(pin_id);
      toggle(pin_id);
    }
  }
}
