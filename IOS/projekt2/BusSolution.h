//=================================================
//            IOS project 2 - The_Senate_Bus_Problem
//  Author: Juraj Lahvička <xlahvi00@vutbr.cz>         
//
//  BusSolution.h created: 2018-Apr-28
//=================================================

/**
 * @brief Initialize semaphores
 */
void initSemaphores();

/**
 * @brief cleans and dealocates all used resources
 */
void cleanup();

/**
 * @brief close semaphores
 */
void closeSemaphores();

/**
 * @brief Solution of The Senate Bus Problem
 * @param riders total number of riders
 * @param busCapacity capacity of bus
 * @param generateNewRiderInterval
 * @param busRideTime
 */
int busSolution(int riders, int busCapacity, int newRiderDelay, int busRideTime);

/**
 * @brief kill process
 */
void processFail();