#ifndef FORKY_H
#define FORKY_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void fork_pattern_one(int number_of_processes);
void fork_pattern_two(int number_of_processes);

#endif // FORKY_H