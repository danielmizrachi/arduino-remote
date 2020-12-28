uint8_t pins[3];
bool states[3] = { false, false, false };

void setup() {
  Serial.begin(9600);
  
  pins[0] = PIN4;
  pins[1] = PIN3;
  pins[2] = PIN2;

  pinMode(PIN4, OUTPUT);
  pinMode(PIN3, OUTPUT);
  pinMode(PIN2, OUTPUT);
}

void toggle(uint8_t pin_id) {
  states[pin_id] = !states[pin_id];
  digitalWrite(pins[pin_id], (uint8_t)states[pin_id]);
}

void loop() {
  int pin_id;

  while (Serial.available() > 0) {
    pin_id = Serial.parseInt() % 3;
    toggle(pin_id);
  }
}
