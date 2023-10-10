#ifndef VISWTIMER_H
#define VISWTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define VISWTIM_NAME_LEN 15
#if !defined(VISWTIM_MAX_TIMERS)
  #define VISWTIM_MAX_TIMERS 20
#endif

void VISWTIM_Init(uint32_t ticksInMs);
bool VISWTIM_Create(const char* name);
bool VISWTIM_Start(const char* name, uint32_t timeoutMs);
bool VISWTIM_isExpired(const char* name);

void VISWTIM_Handler(void);

#ifdef __cplusplus
}
#endif

#endif // VISWTIMER_H