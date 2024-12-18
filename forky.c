#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#include "forky.h"

void process_routine(int process_number)
{
   int sleep_time = 1 + (rand() % 8);
   printf("Process %d (PID: %d) beginning\n", process_number, getpid());
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
         printf("Process %d (PID: %d) exiting\n", ix + 1, getpid());
         exit(EXIT_SUCCESS);
      }
   }

   for (int ix = 0; ix < number_of_processes; ix++)
   {
      pid_t pid = waitpid(pids[ix], 0, 0);
   }
}

void fork_pattern_two(int current_process, int number_of_processes)
{
   if (current_process > number_of_processes)
      return;

   pid_t pid = fork();

   if (pid < 0)
   {
      perror("Fork failed");
      exit(EXIT_FAILURE);
   }

   if (pid == 0)
   {
      process_routine(current_process);
      if (current_process < number_of_processes)
      {
         printf("Process %d (PID: %d) creating process %d\n", current_process, getpid(), current_process + 1);
         fork_pattern_two(current_process + 1, number_of_processes);
      }
      printf("Process %d (PID: %d) exiting\n", current_process, getpid());
      exit(EXIT_SUCCESS);
   }
   else
   {
      waitpid(pid, 0, 0);
   }
}