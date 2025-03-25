#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdbool.h>

typedef struct {
    int pid;
    int burst_time;
    int priority;
    float power_consumption;
    bool is_completed;
    int remaining_time;
} Process;

typedef struct {
    Process* processes;
    int count;
    float total_energy;
    float total_time;
} Scheduler;

Scheduler* create_scheduler(int capacity);
void add_process(Scheduler* scheduler, int pid, int burst_time, int priority, float power_consumption);
void run_energy_efficient_scheduler(Scheduler* scheduler);
void free_scheduler(Scheduler* scheduler);

#endif
