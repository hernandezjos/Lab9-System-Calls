/************************************
* Lab 9 SysProg 111
* @author Joey Hernandez
* @date 10/29/2026
* @file pinfo.c
* compile: Makefile
************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sched.h>
#include <errno.h>
#include <limits.h>

// check the policy 
const char *scheduler_name(int policy)
{
    switch (policy) {
        case SCHED_OTHER:
            return "SCHED_OTHER";
            break;

        case SCHED_FIFO:
            return "SCHED_FIFO";
            break;

        case SCHED_RR:
            return "SCHED_RR";
            break;

            // sched batch and sched idle only work with <sched.h>
        case SCHED_BATCH:
            return "SCHED_BATCH";
            break;

        case SCHED_IDLE:
            return "SCHED_IDLE";
            break;

        default:
            return "Unknown Scheduler";
            break;
    }
}

int main(int argc, char* argv[])
{
    pid_t pid;

    // if no PID was given use current process
    if (argc == 1) {
        pid = getpid();
    }
    // if one was given use it
    else if (argc == 2) {
        char *endptr;
        errno = 0;

        long value = strtol(argv[1], &endptr, 10);

        if (errno != 0 || *endptr != '\0' ||
            value <= 0 || value > INT_MAX) {
            fprintf(stderr, "Invalid PID\n");
            return 1;
        }

        pid = (pid_t)value;
    }
    // if the pid doesnt exist then give a error
    else {
        fprintf(stderr, "Usage: %s [PID]\n", argv[0]);
        return 1;
    }

    // using getpriority, find schedule priority of the pid, check errors
    errno = 0;
    int priority = getpriority(PRIO_PROCESS, pid);
    if (priority == -1 && errno != 0) {
        perror("Error: getpriority");
        return 1;
    }

    // get scheduling policy of pid, check errors
    int policy = sched_getscheduler(pid);
    if (policy == -1) {
        perror("Error: sched_getscheduler");
        return 1;
    }

    // print out pid, priority and its policy
    printf("Process ID: %d\n", pid);
    printf("Priority: %d\n", priority);
    printf("Scheduler: %s\n", scheduler_name(policy));

    return 0;
}