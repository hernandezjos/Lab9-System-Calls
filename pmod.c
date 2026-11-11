/************************************
* Lab 9 SysProg 111
* @author Joey Hernandez
* @date 10/29/2026
* @file pmod.c
* compile: Makefile
************************************/

#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    // reduce priority by adding 10 to nice value with nice(10), check errors
    errno = 0;

    int nice_value = nice(10);

    if (nice_value == -1 && errno != 0) {
        perror("Error: nice");
        return 1;
    }

    printf("Adjusted nice value: %d\n", nice_value);

    // set sleep duration
    struct timespec requested_time;
    struct timespec remaining_time;
    // since requested time is 1837272638 ns take 1000000000 ns = 1 s
    // rewrite to 1s + 837272638 ns
    requested_time.tv_sec = 1;
    requested_time.tv_nsec = 837272638;

    printf("Sleeping...\n"); // for lab check htop during sleep

    // sleep for the specific time and check for errors
    while (nanosleep(&requested_time, &remaining_time) == -1) {

        if (errno == EINTR) {
            requested_time = remaining_time;
        }
        else {
            perror("nanosleep");
            return 1;
        }
    }

    printf("Awake!\n");

    return 0;
}