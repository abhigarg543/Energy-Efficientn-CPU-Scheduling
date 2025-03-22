# Energy Efficient CPU Scheduler

This project implements an energy-aware CPU scheduler that uses Dynamic Voltage and Frequency Scaling (DVFS) to optimize power consumption while maintaining performance.

## Features
- Dynamic frequency scaling based on process priority and completion status
- Power consumption tracking
- Round-robin scheduling with priority consideration
- Energy consumption calculation per process

## Compilation
Using g++:
```bash
g++ -std=c++17 main.cpp scheduler.cpp -o scheduler
```

## Usage
After compilation, run the scheduler:
```bash
./scheduler
```

The program will simulate several processes with different priorities and show their execution along with total energy consumption.
