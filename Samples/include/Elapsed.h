#ifndef ELAPSED_H
#define ELAPSED_H 1
#include "HAL.h"

typedef struct {
  long unsigned lastMS;
} tElapsed;

void ElapsedStart(tElapsed* obj);
bool ElapsedHasExpired(const tElapsed* obj, long unsigned ms);
bool ElapsedHasExpiredRestart(tElapsed* obj, long unsigned ms);

#endif // ELAPSED_H