#include "Elapsed.h"

void ElapsedStart(tElapsed *obj)
{
  obj->lastMS = millis();
}

bool ElapsedHasExpired(const tElapsed *obj, long unsigned ms)
{
    if ((millis() - obj->lastMS) >= ms) {
      return true;
    }
    return false;
}

bool ElapsedHasExpiredRestart(tElapsed *obj, long unsigned ms)
{
  if (ElapsedHasExpired(obj, ms)) {
    ElapsedStart(obj);
    return true;
  }
  return false;
}
