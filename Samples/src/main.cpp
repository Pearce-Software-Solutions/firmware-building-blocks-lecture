#include "HAL.h"

// Define the LESSON value to select which lesson code to compile.
#define LESSON (2)

#if !defined(LESSON)
#error LESSON must be defined
#elif (LESSON == 1)

static const int HeartbeatFlashMS = 1000;

void setup() {
  digitalWrite(HeartbeatLEDPin, LOW);
  pinMode(HeartbeatLEDPin, OUTPUT);
}

void loop() {
  sleep_ms(HeartbeatFlashMS);
  digitalWrite(HeartbeatLEDPin, HIGH);
  sleep_ms(HeartbeatFlashMS);
  digitalWrite(HeartbeatLEDPin, LOW);
}

#elif (LESSON == 2)

static const int HeartbeatFlashMS = 1000;
static unsigned long heartbeatLastMS = 0;
static bool heartbeatState = true;

void setup() {
  digitalWrite(HeartbeatLEDPin, heartbeatState ? HIGH : LOW);
  pinMode(HeartbeatLEDPin, OUTPUT);
  heartbeatLastMS = millis();
}

void loop() {
    if ((millis() - heartbeatLastMS) >= HeartbeatFlashMS) {
      heartbeatLastMS = millis();
      heartbeatState = !heartbeatState;
      digitalWrite(HeartbeatLEDPin, heartbeatState ? HIGH : LOW);
    }
}

#elif (LESSON == 3)

static const unsigned long HeartbeatFlashMS = 1000;
typedef enum {eHeartbeatMode_Off, eHeartbeatMode_On} eHeartbeatMode;
static eHeartbeatMode heartbeatMode = eHeartbeatMode_On;
static bool heartbeatState = false;
static unsigned long heartbeatLastMS = 0;

static bool buttonState = false;

void setup() {
  digitalWrite(HeartbeatLEDPin, LOW);
  pinMode(HeartbeatLEDPin, OUTPUT);
  heartbeatLastMS = millis();

  pinMode(Button1Pin, INPUT_PULLUP);
  buttonState = (digitalRead(Button1Pin) == 0);
}

// If button is short pressed, toggle heartbeat on/off.
void loop() {
  // No longer blocks, so we can process button presses immediately.
  // Now we have a debouncing problem.
  bool newButtonState = (digitalRead(Button1Pin) == 0);
  if (newButtonState != buttonState) {
    buttonState = newButtonState;

    if (buttonState) {
      if (heartbeatMode == eHeartbeatMode_On) {
        heartbeatMode = eHeartbeatMode_Off;
      }
      else {
        heartbeatMode = eHeartbeatMode_On;
      }
    }
  }

  if (heartbeatMode == eHeartbeatMode_On) {
    if ((millis() - heartbeatLastMS) >= HeartbeatFlashMS) {
      heartbeatLastMS = millis();
      heartbeatState = !heartbeatState;
      digitalWrite(HeartbeatLEDPin, heartbeatState ? HIGH : LOW);
    }
  }
  else {
    heartbeatLastMS = millis();
    heartbeatState = false;
    digitalWrite(HeartbeatLEDPin, heartbeatState ? HIGH : LOW);
  }
}

#elif (LESSON == 4)
#include "Heartbeat.h"

static const unsigned long HeartbeatFlashMS = 1000;

static bool buttonState = false;

void setup() {
  HeartbeatInit(HeartbeatLEDPin);
  HeartbeatStart(HeartbeatFlashMS);

  pinMode(Button1Pin, INPUT_PULLUP);
  buttonState = (digitalRead(Button1Pin) == 0);
}

// If button is short pressed, toggle heartbeat on/off.
void loop() {
  HeartbeatUpdate();

  // Still have a debouncing problem.
  bool newButtonState = (digitalRead(Button1Pin) == 0);
  if (newButtonState != buttonState) {
    buttonState = newButtonState;

    if (buttonState) {
      HeartbeatIsRunning() ? HeartbeatStop() : HeartbeatStart(HeartbeatFlashMS);
    }
  }
}

#elif (LESSON == 5)
#include "Heartbeat.h"
#include "Button.h"

static const unsigned long HeartbeatFlashMS = 1000;
static tButton button;

void setup() {
  HeartbeatInit(HeartbeatLEDPin);
  HeartbeatStart(HeartbeatFlashMS);

  ButtonInit(&button, Button1Pin);
}

// If button is short pressed, toggle heartbeat on/off.
void loop() {
  ButtonUpdate(&button);
  HeartbeatUpdate();

  if (ButtonJustPressed(&button)) {
      HeartbeatIsRunning() ? HeartbeatStop() : HeartbeatStart(HeartbeatFlashMS);
  }
}

#elif (LESSON == 6)
#include "Heartbeat.h"
#include "Button.h"

static const unsigned long HeartbeatFlashMS = 1000;
static const unsigned long HeartbeatFlashFastMS = 200;

static tButton button1;
static tButton button2;
static bool buttonWasHeld = false;

void setup() {
  HeartbeatInit(HeartbeatLEDPin);
  HeartbeatStart(HeartbeatFlashMS);

  ButtonInit(&button1, Button1Pin);
  ButtonInit(&button2, Button2Pin);
}

// If button1 is short pressed, toggle heartbeat on/off.
// If button2 is held, flash fast.
void loop() {
  ButtonUpdate(&button1);
  ButtonUpdate(&button2);
  HeartbeatUpdate();

  if (ButtonPressed(&button2)) {
    if (!buttonWasHeld) {
      HeartbeatStart(HeartbeatFlashFastMS);
      buttonWasHeld = true;
    }
  }
  else if (buttonWasHeld) {
      HeartbeatStart(HeartbeatFlashMS);
      buttonWasHeld = false;
  }
  else if (ButtonJustPressed(&button1)) {
      HeartbeatIsRunning() ? HeartbeatStop() : HeartbeatStart(HeartbeatFlashMS);
  }
}

#else
#error Unsupported LESSON value
#endif