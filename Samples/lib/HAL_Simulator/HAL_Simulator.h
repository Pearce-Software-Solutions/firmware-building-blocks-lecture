#ifndef HAL_SIMULATOR_H
#define HAL_SIMULATOR_H 1
#include <cstdint>

typedef uint8_t pin_size_t;

typedef enum {
  LOW     = 0,
  HIGH    = 1,
  CHANGE  = 2,
  FALLING = 3,
  RISING  = 4,
} PinStatus;

typedef enum {
  INPUT            = 0x0,
  OUTPUT           = 0x1,
  INPUT_PULLUP     = 0x2,
  INPUT_PULLDOWN   = 0x3,
  OUTPUT_OPENDRAIN = 0x4,
} PinMode;

void pinMode(pin_size_t pinNumber, PinMode pinMode);
void digitalWrite(pin_size_t pinNumber, PinStatus status);
PinStatus digitalRead(pin_size_t pinNumber);
void sleep_ms(uint32_t ms);
long unsigned millis();

static const int HeartbeatLEDPin = 0;
static const int Button1Pin = 1;
static const int Button2Pin = 2;

struct tPin{
  PinMode mode;
  PinStatus status;
};

tPin& GetPin(pin_size_t pinNumber);

#endif // HAL_SIMULATOR_H