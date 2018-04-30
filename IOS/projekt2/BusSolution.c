//=================================================
//            IOS project 2 - The_Senate_Bus_Problem
//  Author: Juraj Lahvička <xlahvi00@vutbr.cz>         
//
//  BusSolution.c created: 2018-Apr-28
//=================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>

#include "BusSolution.h"
#include "proj2.h"

#define DELAYSLEEP(maxTime) {if (maxTime !=0) usleep((useconds_t) (random() % maxTime * 1000));}
#define FROMGLOBALTOSHARED(pointer) {pointer = mmap(NULL, sizeof(*pointer), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0);}
#define UNMAP(pointer) {munmap(pointer, sizeof(pointer));}
#define LOCKED 0
#define UNLOCKED 1

#define SEMAPHORE1_NAME "/xlahvi00-ios-proj2-semaphore1"
#define SEMAPHORE2_NAME "/xlahvi00-ios-proj2-semaphore2"
#define SEMAPHORE3_NAME "/xlahvi00-ios-proj2-semaphore3"
#define SEMAPHORE4_NAME "/xlahvi00-ios-proj2-semaphore4"

#define LOGFILENAME "proj2.out"

sem_t *semMutex = NULL;
sem_t *semBUS = NULL;
sem_t *semAllAboard = NULL;
sem_t *semEndOfLine = NULL;

// Global variables
int *actionNumber = NULL;
int *numberOfridersShipped = NULL;
int *waitingriders = NULL;

// Log file pointer
FILE *pfile;


void initSemaphores()
{
  semAllAboard = sem_open(SEMAPHORE1_NAME, O_CREAT | O_EXCL, 0666, LOCKED);
  semBUS = sem_open(SEMAPHORE2_NAME, O_CREAT | O_EXCL, 0666, LOCKED);
  semMutex = sem_open(SEMAPHORE3_NAME, O_CREAT | O_EXCL, 0666, UNLOCKED);
  semEndOfLine = sem_open(SEMAPHORE4_NAME, O_CREAT | O_EXCL, 0666, LOCKED);


  if (semAllAboard == SEM_FAILED || semBUS == SEM_FAILED || semMutex == SEM_FAILED || semEndOfLine == SEM_FAILED)
  {
    perror("Error: Semaphore open failed !");
    cleanup();
    exit(2);
  }

  FROMGLOBALTOSHARED(actionNumber);
  FROMGLOBALTOSHARED(numberOfridersShipped);
  FROMGLOBALTOSHARED(waitingriders);

  if (actionNumber == MAP_FAILED || numberOfridersShipped == MAP_FAILED || waitingriders == MAP_FAILED)
  {
    perror("Error: Map failed !");
    cleanup();
    exit(2);
  }

  pfile = fopen(LOGFILENAME, "w");
  if (pfile == NULL)
  {
    perror("Error: Can't open or create log file !");
    cleanup();
    exit(2);
  }

  setbuf(pfile, NULL);
}

/**
 * @brief write start rider info into log file
 * @param id id of rider
 */
void startRider(int id)
{
  (*actionNumber)++;
  fprintf(pfile, "%d: RID %d: start\n", *actionNumber, id);
}

/**
 * @brief write enter rider info into log file
 * @param id id of rider
 */
void enterStation(int id)
{
  (*numberOfridersShipped)++;
  (*waitingriders)++;
  (*actionNumber)++;
  fprintf(pfile, "%d: RID %d: enter: %d\n", *actionNumber, id, *waitingriders);
}

/**
 * @brief write boarding rider info into log file
 * @param id id of rider
 */
void board(int id)
{
  (*actionNumber)++;
  fprintf(pfile, "%d: RID %d: boarding\n", *actionNumber, id);
}

/**
 * @brief write exit rider info into log file
 * @param id id of rider
 */
void exitBus(int id)
{
  (*actionNumber)++;
  fprintf(pfile, "%d: RID %d: finish\n", *actionNumber, id);
}

/**
 * @brief whole process of rider
 * @param id id of rider
 */
void processRider(int id)
{
  // Starting rider
  sem_wait(semMutex);
  startRider(id);
  sem_post(semMutex);

  // Rider has enter station
  sem_wait(semMutex);
  enterStation(id);
  sem_post(semMutex);

  // Rider is boarding
  sem_wait(semBUS);                  // Wait for bus to start boarding
  board(id);
  sem_post(semAllAboard);              // Signal that everybody is aboard

  // Rider is Exiting
  sem_wait(semEndOfLine);
  exitBus(id);
  sem_post(semAllAboard);              // Signal that everybody disembarked
}

/**
 * @brief generate rider
 * @param riders number of riders to generate
 * @param newRiderDelay random delay between each rider
 */
void riderGenerator(int riders, int newRiderDelay)
{
  pid_t newRiderProcess;

  pid_t riderProcessGenerator = fork();
  if (riderProcessGenerator == 0) // Child
  {
    for (int i = 1; i <= riders; i++)
    {
      DELAYSLEEP(newRiderDelay);

      newRiderProcess = fork();
      if (newRiderProcess == 0)
      {
        processRider(i);
        closeSemaphores();
        exit(EXIT_SUCCESS);
      }
      else if (newRiderProcess < 0)
      {
        perror("Error: Fork error!");
        cleanup();
        exit(2);
      }
    }

    /*if (newRiderProcess > 0)
    {
      while (wait(NULL) > 0);
    }*/

    closeSemaphores();
    exit(EXIT_SUCCESS);
  }
  else if (riderProcessGenerator < 0)
  {
    perror("Error: Fork error!");
    cleanup();
    exit(2);
  }
}

/**
 * @brief get minimal value
 * @param a left operand
 * @param b right operand
 * @return minimal value
 */
int getMin(int a, int b)
{
  if (a > b)
  {
    return b;
  }

  return a;
}

/**
 * @brief get maximal value
 * @param a left operand
 * @param b right operand
 * @return maximal value
 */
int getMax(int a, int b)
{
  if (a > b)
  {
    return a;
  }

  return b;
}

/**
 * @brief whole process of bus
 * @param riders total number of riders
 * @param busCapacity bus capacity
 * @param busRideTime random time simulation of bus travel
 */
void processBus(int riders, int busCapacity, int busRideTime)
{

  // BUS is starting
  sem_wait(semMutex);
  (*actionNumber)++;
  fprintf(pfile, "%d: BUS: start\n", *actionNumber);
  sem_post(semMutex);

  static int ridersToBoard;

  while (((*numberOfridersShipped) < riders) || (*waitingriders) != 0)
  {
    // BUS Arrived
    sem_wait(semMutex);
    (*actionNumber)++;
    fprintf(pfile, "%d: BUS: arrival\n", *actionNumber);

    if (ridersToBoard != 0)
    {
      // All riders that are aboard disembark
      for (int i = 0; i < ridersToBoard; i++)
      {
        sem_post(semEndOfLine);
        sem_wait(semAllAboard);         // Waits for all passengers to disembark
      }

      ridersToBoard = 0;
    }

    // If non is waiting depart immediately
    if ((*waitingriders) != 0)
    {
      ridersToBoard = getMin(*waitingriders, busCapacity);
      (*actionNumber)++;
      fprintf(pfile, "%d: BUS: start boarding: %d\n", *actionNumber, ridersToBoard);

      // Get all available riders on board
      for (int i = 0; i < ridersToBoard; i++)
      {
        sem_post(semBUS);         // Bus signals that it has arrived and can take a passenger on board
        sem_wait(semAllAboard);   // Waits for available passengers to get on board
      }

      (*actionNumber)++;
      fprintf(pfile, "%d: BUS: end boarding: %d\n", *actionNumber, *waitingriders - ridersToBoard);
    }


    (*waitingriders) = getMax(*waitingriders - busCapacity, 0);
    (*actionNumber)++;
    fprintf(pfile, "%d: BUS: depart\n", *actionNumber);
    sem_post(semMutex);

    // Simulate travel
    DELAYSLEEP(busRideTime);

    sem_wait(semMutex);
    (*actionNumber)++;
    fprintf(pfile, "%d: BUS: end\n", *actionNumber);
    sem_post(semMutex);
  }

  // Finish
  sem_wait(semMutex);
  (*actionNumber)++;
  fprintf(pfile, "%d: BUS: finish\n", *actionNumber);
  sem_post(semMutex);

  // All left riders disembark
  if (ridersToBoard != 0)
  {
    // All riders that are aboard disembark
    for (int i = 0; i < ridersToBoard; i++)
    {
      sem_post(semEndOfLine);
      sem_wait(semAllAboard);         // Waits for all passengers to disembark
    }

    ridersToBoard = 0;
  }
}

void cleanup()
{
  closeSemaphores();

  // unlink semaphores
  sem_unlink(SEMAPHORE1_NAME);
  sem_unlink(SEMAPHORE2_NAME);
  sem_unlink(SEMAPHORE3_NAME);
  sem_unlink(SEMAPHORE4_NAME);

  UNMAP(actionNumber);
  UNMAP(numberOfridersShipped);
  UNMAP(waitingriders);

  free(params);

  if (pfile != NULL)
    fclose(pfile);

}

void closeSemaphores()
{
  sem_close(semMutex);
  sem_close(semAllAboard);
  sem_close(semBUS);
  sem_close(semEndOfLine);
}

int busSolution(int riders, int busCapacity, int newRiderDelay, int busRideTime)
{
  initSemaphores(busCapacity);

  pid_t busProcess = fork();

  if (busProcess == 0)
  {
    processBus(riders, busCapacity, busRideTime);
    closeSemaphores();
    exit(EXIT_SUCCESS);
  }
  else if (busProcess < 0)
  {
    perror("Error: Fork error!");
    cleanup();
    exit(2);
  }
  else
  {
    riderGenerator(riders, newRiderDelay);
    while (wait(NULL) > 0);
  }

  cleanup();
  return EXIT_SUCCESS;
}

void processFail()
{
  kill(getpid(), SIGTERM);
  cleanup();
  exit(2);
}

