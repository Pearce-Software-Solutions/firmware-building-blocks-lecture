#ifndef HEARTBEAT_H
#define HEARTBEAT_H 1
#include "HAL.h"

void HeartbeatInit(int pin);
void HeartbeatStart(long unsigned ms);
void HeartbeatStop();
bool HeartbeatIsRunning();
void HeartbeatUpdate();

#endif // HEARTBEAT_H