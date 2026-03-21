#include "Debounce.h"

void DebounceInit(tDebounce *obj, bool initialState, long unsigned ms)
{
  *obj = {};
  obj->debouncedState = initialState;
  obj->debounceTimeMS = ms;
  ElapsedStart(&obj->timer);
}

void DebounceUpdate(tDebounce *obj, bool newValue)
{
  if (obj->debouncedState != newValue) {
    if (ElapsedHasExpiredRestart(&obj->timer, obj->debounceTimeMS)) {
      obj->debouncedState = newValue;
    }
  }
  else {
    ElapsedStart(&obj->timer);
  }
}

bool DebounceState(const tDebounce *obj)
{
  return obj->debouncedState;
}
