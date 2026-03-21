#ifndef DEBOUNCE_H
#define DEBOUNCE_H 1
#include "Elapsed.h"

typedef struct {
  bool debouncedState;
  tElapsed timer;
  long unsigned debounceTimeMS;
} tDebounce;

void DebounceInit(tDebounce* obj, bool initialState, long unsigned ms);
void DebounceUpdate(tDebounce* obj, bool newValue);
bool DebounceState(const tDebounce* obj);

#endif // DEBOUNCE_H









