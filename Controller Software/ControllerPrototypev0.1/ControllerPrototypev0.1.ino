void setup() {
  // Initialize LEDs as outputs
  pinMode(4, OUTPUT); // LED for Button 1
  pinMode(5, OUTPUT); // LED for Button 2
  pinMode(6, OUTPUT); // LED for Button 3

  // Initialize buttons as inputs with pull-up
  pinMode(7, INPUT_PULLUP);  // Button 1
  pinMode(8, INPUT_PULLUP);  // Button 2
  pinMode(9, INPUT_PULLUP);  // Button 3

  Serial.begin(9600); // Start serial communication
}

void loop() {
  // Read buttons and control LEDs
  handleButton(7, 4, 'J'); // Jump
  handleButton(8, 5, 'L'); // Left
  handleButton(9, 6, 'R'); // Right
}

void handleButton(int buttonPin, int ledPin, char command) {
  if (digitalRead(buttonPin) == LOW) {
    digitalWrite(ledPin, HIGH);
    Serial.println(command);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
