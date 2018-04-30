//=================================================
//            IOS project 2 - The_Senate_Bus_Problem
//  Author: Juraj Lahvička <xlahvi00@vutbr.cz>         
//
//  proj2.h created: 2018-Apr-28
//=================================================
#ifndef THE_SENATE_BUS_PROBLEM_PROJ2_H
#define THE_SENATE_BUS_PROBLEM_PROJ2_H

typedef struct {
    int riders;
    int busCapacity;
    int newRiderDelay;
    int busRideTime;
} Parameters;

/**
 * @brief pointer to Parameters
 */
Parameters *params;

#endif //THE_SENATE_BUS_PROBLEM_PROJ2_H
