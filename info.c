/************************************
* Lab 9 SysProg 111
* @author Joey Hernandez
* @date 10/29/2026
* @file info.c
* compile: Makefile
************************************/

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/utsname.h>
#include <sys/sysinfo.h>
#include <errno.h>

int main(int argc, char* argv[])
{
    struct timespec current_time;
    struct utsname system_info;
    struct sysinfo memory_info;
    char hostname[256];

    // clock_gettime to retrieve current time for system, check for error
    if (clock_gettime(CLOCK_REALTIME, &current_time) == -1) {
        perror("Error: clock_gettime");
        return 1;
    }

    // print current_time for sec and nanosec
    printf("Current time: %ld seconds, %ld nanoseconds\n",
           current_time.tv_sec, current_time.tv_nsec);

    // use uname to find system info, check errors
    if (uname(&system_info) == -1) {
        perror("Error: uname");
        return 1;
    }

    // print character array buffers from system_info struct from uname
    printf("System: %s\n", system_info.sysname);
    printf("Node: %s\n", system_info.nodename);
    printf("Release: %s\n", system_info.release);
    printf("Version: %s\n", system_info.version);
    printf("Machine: %s\n", system_info.machine);

    // gethostname to get host name, check errors
    if (gethostname(hostname, sizeof(hostname)) == -1) {
        perror("Error: gethostname");
        return 1;
    }

    // print host name back
    printf("Hostname: %s\n", hostname);

    // get_nprocs to get number of processors
    int processors = get_nprocs();

    // print back processor count
    printf("Number of processors: %d\n", processors);

    // use sysconf(_SC_PHYS_PAGES) to find how many pages, 
    // then find how many bytes per page with getpagesize. 
    // Then multiply bytes per page by how many pages to find total phys memory
    long pages = sysconf(_SC_PHYS_PAGES);
    int page_size = getpagesize();

    if (pages != -1) {
        long long total_memory = (long long)pages * page_size;
        printf("Total physical memory: %lld bytes\n", total_memory);
    }

    // use sysinfo()
    if (sysinfo(&memory_info) == 0) {
        unsigned long long free_memory = (unsigned long long)memory_info.freeram * memory_info.mem_unit;

        printf("Free memory: %llu bytes\n", free_memory);
    } else {
        perror("sysinfo");
    }

    return 0;
}
