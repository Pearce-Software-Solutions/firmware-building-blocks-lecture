#ifndef HAL_H
#define HAL_H 1

#define PLATFORM_SIMULATOR 1
#define PLATFORM_PICO2 2

#if (PLATFORM == PLATFORM_SIMULATOR)
#include "HAL_Simulator.h"
#elif (PLATFORM == PLATFORM_PICO2)
#include "HAL_Pico2.h"
#else
#error PLATFORM must be defined as a supported value
#endif

#endif // HAL_H