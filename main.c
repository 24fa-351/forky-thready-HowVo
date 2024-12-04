#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "forky.h"

int main(int argc, char *argv[])
{
    int min;
    int max;
    int pattern_number;
    sscanf(argv[1], "%d", &min);
    sscanf(argv[2], "%d", &max);
    sscanf(argv[3], "%d", &pattern_number);


    if (argc != 4)
    {
        printf("Usage: %s <min> <max> <pattern_number>\n", argv[0]);
        return 1;
    }


    int number_of_processes = max - min + 1;
    if (pattern_number == 1)
    {
        fork_pattern_one(number_of_processes);
    }
    else if (pattern_number == 2)
    {
        fork_pattern_two(number_of_processes);
    }
    else
    {
        printf("Invalid pattern number. Pick 1 or 2\n");
        return 1;
    }


    return 0;
}
