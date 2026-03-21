#ifndef BUTTON_H
#define BUTTON_H 1
#include "HAL.h"
#include "Elapsed.h"
#include "Debounce.h"

typedef struct {
  int pin;
  tElapsed heldTimer;
  tDebounce debouncer;
  bool state;
  bool lastState;
} tButton;

void ButtonInit(tButton* obj, int pin);
void ButtonUpdate(tButton* obj);
bool ButtonPressed(const tButton* obj);
bool ButtonReleased(const tButton* obj);
bool ButtonJustChanged(const tButton* obj);
bool ButtonJustPressed(const tButton* obj);
bool ButtonJustReleased(const tButton* obj);
bool ButtonHeld(const tButton* obj, long unsigned ms);

#endif // BUTTON_H