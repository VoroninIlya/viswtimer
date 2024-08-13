/**
 * @file viswtimer.c
 * @author Ilia Voronin (www.linkedin.com/in/ilia-voronin-7a169122a)
 * @brief Source file of viswtimer (software timers) driver
 * 
 * @copyright Copyright (c) 2023Ilia Voronin
 * 
 * This software is licensed under GNU GENERAL PUBLIC LICENSE 
 * The terms can be found in the LICENSE file in
 * the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS,
 * Without warranty of any kind, express or implied, 
 * including but not limited to the warranties of merchantability, 
 * fitness for a particular purpose and noninfringement. 
 * In no event shall the authors or copyright holders be liable for any claim, 
 * damages or other liability, whether in an action of contract, tort or otherwise, 
 * arising from, out of or in connection with the software 
 * or the use or other dealings in the software.
 * 
 */

#include "viswtimer_private.h"
#include "string.h"

/**
 * @brief array of all software timers
 * 
 */
static struct {
  Timer_t tm[VISWTIM_MAX_TIMERS];
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
  int32_t timerIndex = FindTimerByName(name);
  if(0 <= timerIndex)
    return false;
  if(Init(&timers.tm[timers.initializedNumber], name)) {
    timers.initializedNumber++;
    return true;
  }
  return false;
}

bool VISWTIM_Start(const char* name, uint32_t timeoutMs) {
  int32_t timerIndex = FindTimerByName(name);
  if(0 <= timerIndex)
    return Start(&timers.tm[timerIndex], timeoutMs * timers.ticksInMs);
  return false;
}

bool VISWTIM_IsExpired(const char* name){
  int32_t timerIndex = FindTimerByName(name);
  if(0 <= timerIndex)
    return IsExpired(&timers.tm[timerIndex]);
  return false;
}

void VISWTIM_Handler(void){
  uint32_t index = 0;
  while((index < VISWTIM_MAX_TIMERS) && (0 < strlen(timers.tm[index].name))) {
    TickHandler(&timers.tm[index++]);
  }
}

static bool Init(Timer_t* timer, const char* name) {
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

static bool Start(Timer_t* timer, uint32_t timeoutMs) {
  if((NULL == timer) || (0 == timeoutMs))
    return false;
  timer->tick = timeoutMs;
  timer->enabled = true;
  timer->isExpired = false;
  return true;
}

static bool IsExpired(Timer_t* timer) {
  if(NULL == timer) 
    return false;
  return timer->isExpired;
}

static void TickHandler(Timer_t* timer) {
  if(NULL == timer)
    return;

  if((timer->enabled) && (0 < timer->tick))
    timer->tick -= 1;
  else if ((timer->enabled) && (0 == timer->tick)) {
    timer->enabled = false;
    timer->isExpired = true;
  }
}

static int32_t FindTimerByName(const char* name) {
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
