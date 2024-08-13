/**
 * @file viswtimer_private.h
 * @author Ilia Voronin (www.linkedin.com/in/ilia-voronin-7a169122a)
 * @brief Private header file of viswtimer (software timers) driver
 *
 * @copyright Copyright (c) 2023 Ilia Voronin
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

#ifndef VISWTIMER_PRIVATE_H
#define VISWTIMER_PRIVATE_H

#include "viswtimer.h"

/**
 * @brief Timer control type
 * 
 */
typedef struct {
  char name[VISWTIM_NAME_LEN]; /*!< name of timer */
  uint32_t tick;               /*!< timer tick counter */
  bool enabled;                /*!< enabled flag */
  bool isExpired;              /*!< expiered flag */
}Timer_t;

/**
 * @brief Initialize a timer control structure
 * 
 * @param timer Timer control structure instance
 * @param name Unique timer name
 * @return true if initialization is successful
 * @return false if initialization is failed
 */
static bool Init(Timer_t* timer, const char* name);

/**
 * @brief Start timer
 * 
 * @param timer Timer control structure instance
 * @param timeoutMs Timeout in milliseconds until timer expiration
 * @return true if start is successful
 * @return false if any error occurred by start
 */
static bool Start(Timer_t* timer, uint32_t timeoutMs);

/**
 * @brief Check if timer is expiered
 * 
 * @param timer Timer control structure instance
 * @return true if timer has expired
 * @return false if timer hasn't expired
 */
static bool IsExpired(Timer_t* timer);

/**
 * @brief Timer tick handler
 * 
 * @param timer Timer control structure instance
 */
static void TickHandler(Timer_t* timer);

/**
 * @brief Find timer by name in array of timers
 * 
 * @param name Timer name to search
 * @return int32_t index of found timer, if no timer found returns -1
 */
static int32_t FindTimerByName(const char* name);

#endif // VISWTIMER_PRIVATE_H

