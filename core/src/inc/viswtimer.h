/**
 * @file viswtimer.h
 * @author Ilia Voronin (www.linkedin.com/in/ilia-voronin-7a169122a)
 * @brief Header file of viswtimer (software timers) driver
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

#ifndef VISWTIMER_H
#define VISWTIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

/** 
 * @brief Maximal length of a timer name.
 *   All names longer this limit will be cutted until this limit
 * */ 
#if !defined(VISWTIM_NAME_LEN)
  #define VISWTIM_NAME_LEN 15     
#endif

/** 
 * @brief Maximal number of allowed to create timers.
 *   For this number of timers will be static memory reserved 
 * */
#if !defined(VISWTIM_MAX_TIMERS)
  #define VISWTIM_MAX_TIMERS 20   
#endif

/**
 * @brief Initialization of software timers driver
 * 
 * @param[in] ticksInMs The number of ticks in one millisecond.
 *   In other words: how much times per millisecond will be called VISWTIM_Handler.
 *   This value is multiplying with timeoutMs by call VISWTIM_Start
 */
void VISWTIM_Init(uint32_t ticksInMs);

/**
 * @brief Create/register a new timer
 * 
 * @param[in] name Unique name of timer. Care about VISWTIM_NAME_LEN
 * @return true if timer created successfull
 * @return false if any error occurred through creation
 */
bool VISWTIM_Create(const char* name);

/**
 * @brief Start timer with defined name, that has been created before
 * 
 * @param[in] name Unique name of timer
 * @param[in] timeoutMs Number of milliseconds until timer expiration
 * @return true if timer started successfull
 * @return false if any error occurred by start
 */
bool VISWTIM_Start(const char* name, uint32_t timeoutMs);

/**
 * @brief Check if timer with defined name expired, 
 *   if timer wasn't started before, funktion returned always false
 * @param[in] name Unique name of timer
 * @return true if timer has expiered
 * @return false if timer hasn't expiered
 */
bool VISWTIM_IsExpired(const char* name);

/**

 * @brief Driver runtime, should be placed in systick handler
 */
void VISWTIM_Handler(void);

#ifdef __cplusplus
}
#endif

#endif // VISWTIMER_H