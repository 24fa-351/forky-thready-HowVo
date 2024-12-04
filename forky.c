#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#include "forky.h"

void process_routine(int process_number)
{
   srand(time(NULL));
   int sleep_time = 1 + (rand() % 8);
   printf("Process %d beginning\n", process_number);
   sleep(sleep_time);
}

void fork_pattern_one(int number_of_processes)
{
   pid_t pids[number_of_processes];

   for (int ix = 0; ix < number_of_processes; ++ix)
   {
      pids[ix] = fork();

      if (pids[ix] < 0)
      {
         perror("Fork failed");
         exit(EXIT_FAILURE);
      }

      if (pids[ix] == 0)
      {
         process_routine(ix + 1);
         printf("Process %d exiting\n", ix + 1);
         exit(EXIT_SUCCESS);
      }
   }

   for (int ix = 0; ix < number_of_processes; ix++)
   {
      pid_t pid = waitpid(pids[ix], 0, 0);
   }
}

void fork_pattern_two(int number_of_processes)
{
   for (int ix = 0; ix < number_of_processes; ++ix)
   {
      pid_t pid = fork();

      if (pid < 0)
      {
         perror("Fork failed");
         exit(EXIT_FAILURE);
      }

      if (pid == 0)
      {
         process_routine(ix + 1);
         if (ix < number_of_processes - 1)
         {
            printf("Process %d creating process %d\n", ix + 1, ix + 2);
         }
      }
      else
      {
         waitpid(pid, 0, 0);
         printf("Process %d exiting\n", ix + 1);
         break;
      }
   }
}