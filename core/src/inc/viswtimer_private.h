#ifndef VISWTIMER_PRIVATE_H
#define VISWTIMER_PRIVATE_H

#include "viswtimer.h"
#include "string.h"

typedef struct {
  char name[VISWTIM_NAME_LEN];
  uint32_t tick;
  bool enabled;
  bool isExpired;
}Control_t;

static bool Init(Control_t* timer, const char* name);
static bool Start(Control_t* timer, uint32_t timeout);
static bool isExpired(Control_t* timer);
static void TickHandler(Control_t* timer);
static int32_t findTimerByName(const char* name);

#endif // VISWTIMER_PRIVATE_H

