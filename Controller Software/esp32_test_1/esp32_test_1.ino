#include <BluetoothSerial.h>

#define LED_PIN 13
#define BUTTON_A_PIN 12
#define BUTTON_LEFT_PIN 14
#define BUTTON_RIGHT_PIN 27

BluetoothSerial SerialBT;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);

  SerialBT.begin("ESP32 Gamepad"); // Bluetooth device name
  Serial.begin(9600); // Start serial communication
}

void loop() {
  // Read button states
  int buttonAState = digitalRead(BUTTON_A_PIN);
  int buttonLeftState = digitalRead(BUTTON_LEFT_PIN);
  int buttonRightState = digitalRead(BUTTON_RIGHT_PIN);

  // Update LED based on button A state
  digitalWrite(LED_PIN, buttonAState == LOW ? HIGH : LOW);

  // Construct the data packet
  uint8_t data[4];
  data[0] = buttonAState;
  data[1] = buttonLeftState;
  data[2] = buttonRightState;
  data[3] = '\n'; // End marker

  // Send the data packet over Bluetooth
  SerialBT.write(data, sizeof(data));

  // Print the data to USB serial
  Serial.print("Button A: ");
  Serial.print(data[0]);
  Serial.print(", Button Left: ");
  Serial.print(data[1]);
  Serial.print(", Button Right: ");
  Serial.println(data[2]);

  delay(50); // Adjust as needed
}
