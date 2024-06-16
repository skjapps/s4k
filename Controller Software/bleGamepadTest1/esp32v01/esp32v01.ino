#include <Arduino.h>
#include <BleGamepad.h>

// The bluetooth LE Gamepad Library
BleGamepad bleGamepad("SKJAPPS Controller", "skjapps", 100);

// Inputs
#define BUTTON_A_PIN 13
#define BUTTON_LEFT_PIN 12
#define BUTTON_RIGHT_PIN 14

void setup() {
  // Hardware
  pinMode(BUTTON_A_PIN, INPUT_PULLUP);
  pinMode(BUTTON_LEFT_PIN, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT_PIN, INPUT_PULLUP);

  // Serial Debugging
  Serial.begin(115200);
  Serial.println("Starting BLE work!");

  // BLE
  BleGamepadConfiguration bleGamepadConfig;
  // CONTROLLER_TYPE_JOYSTICK, CONTROLLER_TYPE_GAMEPAD (DEFAULT), CONTROLLER_TYPE_MULTI_AXIS
  bleGamepadConfig.setControllerType(CONTROLLER_TYPE_GAMEPAD); 
  // Logitech Standard Gamepad
  bleGamepadConfig.setVid(0x046D);
  bleGamepadConfig.setPid(0xC216);
  // Only X axis (left thumb x)
  bleGamepadConfig.setWhichAxes(true, false, false, false, false, false, false, false);
  // Start the gamepad service
  bleGamepad.begin(&bleGamepadConfig);
}

void loop() {
  // if the controller is connected, can send inputs
  if (bleGamepad.isConnected())
  {
    // Read button states
    int buttonAState = digitalRead(BUTTON_A_PIN);
    int buttonLeftState = digitalRead(BUTTON_LEFT_PIN);
    int buttonRightState = digitalRead(BUTTON_RIGHT_PIN);
    
	// Log buttons in serial output
    Serial.printf("Button A: %d, Left Button: %d, Right Button: %d \n", buttonAState, buttonLeftState, buttonRightState);

    // Press Button 1 for A
    if(!buttonAState) {
      bleGamepad.press(BUTTON_2);
    } else {
      bleGamepad.release(BUTTON_2);
    }
    
    // 0 = Left, 16384 = Middle, 32767 = Right
    if(!buttonLeftState) {
      bleGamepad.setLeftThumb(0, 16384);
    } else if (!buttonRightState) {
      bleGamepad.setLeftThumb(32767, 16384);
    } else {
      bleGamepad.setLeftThumb(16383, 16384);
    }

  }
}
