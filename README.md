# XV6 Lottery Scheduler Project

## Overview
This project involves modifying the xv6 operating system, a simple Unix-like teaching operating system, to implement a lottery scheduler. This scheduler assigns processor time slices to running processes based on the number of tickets they hold, with processes having more tickets getting proportionally more CPU time.

## Objectives
- **Understand the xv6 Kernel**: Gain deeper knowledge of a real operating system kernel.
- **Learn about Schedulers**: Familiarize with the concept and implementation of an OS scheduler.
- **Implement Lottery Scheduler**: Replace the existing round-robin scheduler with a lottery scheduler.
- **Graphical Representation**: Create a graph to demonstrate the behavior of the new scheduler.

## Key Components

### Setting Tickets
- **System Call**: Implement a new system call `int settickets(int)` to set the number of tickets for the calling process.
- **Default Tickets**: Each process starts with one ticket.
- **Return Values**: The system call returns `0` on success and `-1` on failure (e.g., if the number of tickets is less than one).

### Implementing the Scheduler
- **Location**: The scheduler code is primarily in `proc.c`, with `proc.h` being a useful reference.
- **Modification**: Replace the round-robin code in `proc.c` with the lottery scheduler implementation.
- **Inheritance**: Ensure child processes inherit the ticket count from their parent.
- **Random Number Generation**: Incorporate a pseudo-random number generator for the lottery mechanism.

### Getting Process Statistics
- **System Call**: Implement `int getpinfo(struct pstat *)` to gather statistics about running processes.
- **Usage**: Use this call to build a variant of `ps` to monitor process status.
- **Structure**: Utilize the `pstat` structure as defined, without modifications.

### Source Code
- **Location**: The xv6 source code for this project is located at `/cs5348-xv6/src/xv6.tar.gz`.
- **Setup**: Extract the source code using `tar –zxvf xv6.tar.gz`.

### Testing
- **Test Programs**: Located in `/cs5348-xv6/src/testcases/P2/`. Copy these to the `.../xv6/user/` directory.
- **Compilation**: Compile the test programs and rebuild the xv6 kernel with them included.
- **Graph**: Create a graph showing the time slices received by three processes with a 3:2:1 ticket ratio.

### Configuration
- **CPU Limitation**: Use only one CPU for this project (`make qemu CPUS=1`), as the default setting of two CPUs may cause test failures.

