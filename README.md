# Lab 9 - Linux System Calls

Author: Your Name

## Description

This lab explores Linux system calls and system-level programming
using C.

## Programs

### info.c
Displays system information, including:
- Current time
- Hostname
- Operating system information
- Number of processors
- Physical memory information

### pinfo.c
Displays process information, including:
- Process ID
- Process priority
- Scheduling policy

### pmod.c
Modifies the process nice value and uses nanosleep()
to pause execution.

### finfo.c
Displays file information, including:
- File type
- File permissions
- Owner UID
- File size
- Last modification time

## Compilation

Compile all programs:

    make

Remove executables:

    make clean

## Running Programs

    ./info

    ./pinfo

    ./pinfo 1234

    ./pmod

    ./finfo filename.txt