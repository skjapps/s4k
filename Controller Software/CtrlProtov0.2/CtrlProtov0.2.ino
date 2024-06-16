#include <ArduinoBLE.h>

const int LED_PIN = 2;

// Define digital pins for buttons
const int LEFT_BUTTON_PIN = 5;
const int RIGHT_BUTTON_PIN = 4;
const int A_BUTTON_PIN = 3;

// Define BLE service and characteristics
BLEService gamepadService("1812"); // HID Service UUID

BLEUnsignedCharCharacteristic buttonsCharacteristic("2A56", BLERead | BLENotify); // HID Report Map characteristic UUID

void setup() {
  // Initialize digital pins for buttons
  pinMode(LEFT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(RIGHT_BUTTON_PIN, INPUT_PULLUP);
  pinMode(A_BUTTON_PIN, INPUT_PULLUP);
  
  // Begin BLE
  if (!BLE.begin()) {
    while (1);
  }
  
  // Set the local name peripheral advertising packet
  BLE.setLocalName("Gamepad");
  // Add the HID service
  BLE.addService(gamepadService);
  // Add the HID Report Map characteristic
  gamepadService.addCharacteristic(buttonsCharacteristic);
  
  // Set initial button states
  updateButtonsCharacteristic();
  
  // Start advertising BLE peripheral
  BLE.advertise();
}

void loop() {
  // Update button states
  updateButtonsCharacteristic();
  
  // Delay for stability
  delay(50);
}

void updateButtonsCharacteristic() {
  // Create buffer for HID report
  uint8_t hidReport[1];
  // Set button states in the HID report
  hidReport[0] = 0;
  if (digitalRead(LEFT_BUTTON_PIN) == LOW) {
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    hidReport[0] |= B00000001; // Left button
  }
  else if (digitalRead(RIGHT_BUTTON_PIN) == LOW) {
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    hidReport[0] |= B00000010; // Right button
  }
  else if (digitalRead(A_BUTTON_PIN) == LOW) {
    digitalWrite(LED_PIN, HIGH); // Turn on LED
    hidReport[0] |= B00010000; // A button
  } else {
    digitalWrite(LED_PIN, LOW); // Turn off LED
  }
  // Update characteristic with HID report
  buttonsCharacteristic.writeValue(hidReport[0]);
}
