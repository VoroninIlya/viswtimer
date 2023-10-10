#include "viswtimer_private.h"

static struct {
  Control_t tm[VISWTIM_MAX_TIMERS];
  uint32_t initializedNumber;
  uint32_t ticksInMs;
}timers;

void VISWTIM_Init(uint32_t ticksInMs) {
  timers.ticksInMs = (ticksInMs > 0)? ticksInMs : 1; 
  timers.initializedNumber = 0;
  for(uint32_t i = 0; i < VISWTIM_MAX_TIMERS; i++) {
    Init(&timers.tm[i], NULL);
  }
}

bool VISWTIM_Create(const char* name) {
  if(NULL == name)
    return false;
  if(VISWTIM_MAX_TIMERS <= timers.initializedNumber)
    return false;
  int32_t timerIndex = findTimerByName(name);
  if(0 <= timerIndex)
    return false;
  if(Init(&timers.tm[timers.initializedNumber], name)) {
    timers.initializedNumber++;
    return true;
  }
  return false;
}

bool VISWTIM_Start(const char* name, uint32_t timeoutMs) {
  int32_t timerIndex = findTimerByName(name);
  if(0 <= timerIndex)
    return Start(&timers.tm[timerIndex], timeoutMs * timers.ticksInMs);
  return false;
}

bool VISWTIM_isExpired(const char* name){
  int32_t timerIndex = findTimerByName(name);
  if(0 <= timerIndex)
    return isExpired(&timers.tm[timerIndex]);
  return false;
}

void VISWTIM_Handler(void){
  uint32_t index = 0;
  while((index < VISWTIM_MAX_TIMERS) && (0 < strlen(timers.tm[index].name))) {
    TickHandler(&timers.tm[index++]);
  }
}

static bool Init(Control_t* timer, const char* name) {
  if(NULL == timer)
    return false;
  if(name == NULL)
    memset(timer->name, 0, VISWTIM_NAME_LEN);
  else
    strncpy(timer->name, name, VISWTIM_NAME_LEN);
  timer->tick = 0;
  timer->enabled = false;
  timer->isExpired = false;
  return true;
}

static bool Start(Control_t* timer, uint32_t timeout) {
  if((NULL == timer) || (0 == timeout))
    return false;
  timer->tick = timeout;
  timer->enabled = true;
  timer->isExpired = false;
  return true;
}

static bool isExpired(Control_t* timer) {
  if(NULL == timer) 
    return false;
  return timer->isExpired;
}

static void TickHandler(Control_t* timer) {
  if(NULL == timer)
    return;

  if((timer->enabled) && (0 < timer->tick))
    timer->tick -= 1;
  else if ((timer->enabled) && (0 == timer->tick)) {
    timer->enabled = false;
    timer->isExpired = true;
  }
}

static int32_t findTimerByName(const char* name) {
  int32_t result = -1;
  if(NULL == name)
    return result;
  for(uint32_t i = 0; ((i < VISWTIM_MAX_TIMERS) && (i < timers.initializedNumber)); i++) {
    if(0 == strncmp(timers.tm[i].name, name, VISWTIM_NAME_LEN)) {
      result = i;
    }
  }
  return result;
}
