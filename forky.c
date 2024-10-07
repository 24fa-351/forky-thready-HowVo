#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char **argv)
{
   unsigned int numOfProcess = atoi(argv[1]);
   unsigned int patternNum = atoi(argv[2]);
   pid_t childPid;
   srand(time(NULL));

   if (patternNum == 1)
   {
      for (unsigned int i = 0; i < numOfProcess; i++)
      {
         childPid = fork();
         int sleepTime = rand() % 8 + 1;

         if (childPid < 0)
         {
            perror("Fork failed");
         }

         else if (childPid == 0) // in child process
         {
            printf("Process %d (%d) beginning\n", i + 1, getpid());
            sleep(sleepTime);
            printf("Process %d (%d) exiting after sleeping for %d second(s), the parent is %d\n", i + 1, getpid(), sleepTime, getppid());
            exit(0);
         }
      }

      for (unsigned int i = 0; i < numOfProcess; i++)
      {
         wait(NULL);
      }
   }

   else if (patternNum == 2)
   {
      for (unsigned int i = 1; i <= numOfProcess - 1; i++)
      {
         childPid = fork();
         int sleepTime = rand() % 8 + 1;

         if (childPid < 0)
         {
            perror("Fork failed");
         }

         else if (childPid > 0) // in parent process
         {
            printf("Process %d (%d) beginning\n", i, getpid());
            printf("Process %d creating Process %d\n", i, i + 1);
            wait(NULL);
            exit(0);
         }

         else // in child process
         {
            sleep(sleepTime);
            printf("Process %d exiting\n", i);
            printf("Process %d (%d) started Process %d (%d)\n", i, getppid(), i + 1, getpid());
         }
      }
   }
   return 0;
}
