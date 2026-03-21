#include "Heartbeat.h"
#include "Elapsed.h"

typedef enum {eState_Stopped, eState_Off, eState_On} eState;

typedef struct {
  int pin;
  long unsigned ms;
  tElapsed elapsed;
  eState state;
  eState lastState;
} tHeartbeat;
static tHeartbeat heartbeat {};

void SetLED(bool value)
{
  digitalWrite(heartbeat.pin, value ? HIGH : LOW);
}

void HeartbeatInit(int pin)
{
  heartbeat = {};
  heartbeat.pin = pin;
  SetLED(false);
  pinMode(heartbeat.pin, OUTPUT);
}

void HeartbeatStart(long unsigned ms)
{
  heartbeat.ms = ms;
  heartbeat.state = eState_On;
  SetLED(true);
}

void HeartbeatStop()
{
  heartbeat.state = eState_Stopped;
}

bool HeartbeatIsRunning()
{
  return heartbeat.state != eState_Stopped;
}

void HeartbeatUpdate()
{
  bool firstTime = heartbeat.state != heartbeat.lastState;
  heartbeat.lastState = heartbeat.state;

  switch (heartbeat.state) {
    case eState_Stopped:
      if (firstTime) {
        SetLED(false);
      }
      break;
    case eState_Off:
      if (firstTime) {
        SetLED(false);
        ElapsedStart(&heartbeat.elapsed);
      }
      if (ElapsedHasExpired(&heartbeat.elapsed, heartbeat.ms)) {
        heartbeat.state = eState_On;
      }
      break;
    case eState_On:
      if (firstTime) {
        SetLED(true);
        ElapsedStart(&heartbeat.elapsed);
      }
      if (ElapsedHasExpired(&heartbeat.elapsed, heartbeat.ms)) {
        heartbeat.state = eState_Off;
      }
      break;
  }
}
