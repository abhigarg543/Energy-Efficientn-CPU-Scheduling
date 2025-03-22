#include "scheduler.hpp"
#include <iostream>

int main() {
    EnergyEfficientScheduler scheduler;

    // Create some test processes with different priorities and burst times
    // Parameters: (pid, burst_time, arrival_time, priority)
    scheduler.addProcess(std::make_shared<Process>(1, 5.0, 0.0, 4));   // High priority
    scheduler.addProcess(std::make_shared<Process>(2, 3.0, 1.0, 2));   // Medium priority
    scheduler.addProcess(std::make_shared<Process>(3, 8.0, 2.0, 1));   // Low priority
    scheduler.addProcess(std::make_shared<Process>(4, 2.0, 3.0, 3));   // Medium priority

    std::cout << "Starting energy-efficient CPU scheduler simulation...\n\n";
    
    scheduler.run();

    std::cout << "\nSimulation completed!\n";
    std::cout << "Total energy consumption: " << scheduler.getTotalEnergyConsumption() << " watts\n";

    return 0;
}
