
uint8_t MOTOR = D1;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(MOTOR, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(MOTOR, HIGH);   // turn the LED on (HIGH is the voltage level)
}
