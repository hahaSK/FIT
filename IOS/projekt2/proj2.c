#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <signal.h>

#include "BusSolution.h"
#include "proj2.h"

#define COLOR_GREEN "\033[32m"
#define COLOR_RESET "\x1b[0m"

Parameters *parameterParser(int argc, char *argv[])
{
  // first argument is filename
  if (argc - 1 != 4)
  {
    perror("Error: Number of arguments must be 4 !\n");
    exit(EXIT_FAILURE);
  }

  char *endptr;

  int riders = strtol(argv[1], &endptr, 10);
  if (riders <= 0 || *endptr != '\0')
  {
    perror("Error: Riders argument must be integer from interval: "
           COLOR_GREEN "R > 0\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  int busCapacity = strtol(argv[2], &endptr, 10);
  if (busCapacity <= 0 || *endptr != '\0')
  {
    perror("Error: BUS capacity argument must be integer from interval: "
           COLOR_GREEN "C > 0\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  int newRiderDelay = strtol(argv[3], &endptr, 10);
  if (newRiderDelay < 0 || newRiderDelay > 1000 || *endptr != '\0')
  {
    perror("Error: New Rider Delay argument must be integer from interval: "
           COLOR_GREEN "0 =< ART <= 1000\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  int busRideTime = strtol(argv[4], &endptr, 10);
  if (busRideTime < 0 || busRideTime > 1000 || *endptr != '\0')
  {
    perror("Error: Bus Ride Time argument must be integer from interval: "
           COLOR_GREEN "0 =< ABT <= 1000\n" COLOR_RESET);
    exit(EXIT_FAILURE);
  }

  Parameters *parsedParameters = NULL;
  parsedParameters = malloc(sizeof(Parameters));

  // Check if malloc failed
  if (parsedParameters == NULL) {
    perror("ERROR: Failed malloc for Parameters struct!");
    exit(2);
  }

  parsedParameters->riders = riders;
  parsedParameters->busCapacity = busCapacity;
  parsedParameters->newRiderDelay = newRiderDelay;
  parsedParameters->busRideTime = busRideTime;

  return parsedParameters;
}

int main(int argc, char *argv[])
{
  // Get and check Input parameters
  params = parameterParser(argc, argv);

  signal(SIGINT, processFail);
  signal(SIGTERM, processFail);

  busSolution(params->riders, params->busCapacity, params->newRiderDelay, params->busRideTime);

  return 0;
}