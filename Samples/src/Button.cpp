#include "Button.h"

void ButtonInit(tButton *obj, int pin)
{
  *obj = {};
  obj->pin = pin;
  pinMode(obj->pin, INPUT_PULLUP);
  obj->state = (digitalRead(obj->pin) == 0);
  obj->lastState = obj->state;
  DebounceInit(&obj->debouncer, obj->state, 50);
}

void ButtonUpdate(tButton *obj)
{
  obj->lastState = obj->state;
  DebounceUpdate(&obj->debouncer, (digitalRead(obj->pin) == 0));
  obj->state = DebounceState(&obj->debouncer);

  if (ButtonJustPressed(obj)) {
    ElapsedStart(&obj->heldTimer);
  }
}

bool ButtonPressed(const tButton *obj)
{
  return obj->state;
}

bool ButtonReleased(const tButton *obj)
{
  return !obj->state;
}

bool ButtonJustChanged(const tButton *obj)
{
  return (obj->state != obj->lastState);
}

bool ButtonJustPressed(const tButton *obj)
{
  if (obj->state != obj->lastState) {
    return obj->state;
  }
  return false;
}

bool ButtonJustReleased(const tButton *obj)
{
  if (obj->state != obj->lastState) {
    return !obj->state;
  }
  return false;
}

bool ButtonHeld(const tButton *obj, long unsigned ms)
{
  if (ButtonPressed(obj) && ElapsedHasExpired(&obj->heldTimer, ms)) {
    return true;
  }
  return false;
}
