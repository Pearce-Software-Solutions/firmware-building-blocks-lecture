#include "HAL_Simulator.h"
#include <array>
#include "unistd.h"
#include <chrono>
#include "GUI.h"

std::array<tPin, 256> pins;

tPin &GetPin(pin_size_t pinNumber)
{
  return pins.at(pinNumber);
}

void pinMode(pin_size_t pinNumber, PinMode pinMode)
{
  GetPin(pinNumber).mode = pinMode;
  if (pinMode == INPUT_PULLUP) {
    GetPin(pinNumber).status = HIGH;
  }
  else if (pinMode == INPUT_PULLDOWN) {
    GetPin(pinNumber).status = LOW;
  }
}

void digitalWrite(pin_size_t pinNumber, PinStatus status)
{
  GetPin(pinNumber).status = status;
}

PinStatus digitalRead(pin_size_t pinNumber)
{
  return GetPin(pinNumber).status;
}

void sleep_ms(uint32_t ms)
{
  usleep(ms * 1000);
}

long unsigned millis()
{
  static auto start = std::chrono::steady_clock::now();
  auto now = std::chrono::steady_clock::now();
  auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(now - start);
  return elapsed.count();
}

extern void setup();
extern void loop();

int main()
{
  setup();

	tGUI gui;

	while (!gui.ExitRequested()) {
    gui.SetLEDState(digitalRead(HeartbeatLEDPin) == HIGH);
    digitalWrite(Button1Pin, gui.InputState(0) ? LOW : HIGH);
    digitalWrite(Button2Pin, gui.InputState(1) ? LOW : HIGH);
		gui.UpdateGUI();
    loop();
	}
}