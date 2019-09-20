

// digital pin 2 has a pushbutton attached to it. Give it a name:
uint8_t irSensor = D3;
uint8_t LED = D4;
uint8_t MOTOR = D1;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  // make the pushbutton's pin an input:
  pinMode(irSensor, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(MOTOR, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input pin:
  int irState = digitalRead(irSensor);
  // print out the state of the button:
  //Serial.println(irState);
  digitalWrite(LED, !(irState));
  delay(1);        // delay in between reads for stability
  digitalWrite(MOTOR,!(irState));   // turn the LED on (HIGH is the voltage level)
}
