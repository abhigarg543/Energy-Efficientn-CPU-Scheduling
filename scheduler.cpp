#include "scheduler.hpp"
#include <algorithm>
#include <iostream>

EnergyEfficientScheduler::EnergyEfficientScheduler() 
    : currentTime(0), totalEnergyConsumption(0) {}

void EnergyEfficientScheduler::addProcess(std::shared_ptr<Process> process) {
    processes.push_back(process);
}

void EnergyEfficientScheduler::adjustFrequency(std::shared_ptr<Process> process) {
    // Simple DVFS strategy:
    // - High priority processes run at higher frequencies
    // - Processes with shorter remaining time run at lower frequencies
    if (process->priority > 3) {
        process->frequencyLevel = 4; // Higher frequency for high priority
    } else if (process->remainingTime < process->burstTime * 0.3) {
        process->frequencyLevel = 2; // Lower frequency for nearly completed processes
    } else {
        process->frequencyLevel = 3; // Default middle frequency
    }
}

double EnergyEfficientScheduler::calculateEnergyConsumption(std::shared_ptr<Process> process, double timeSlice) const {
    return powerConsumption[process->frequencyLevel - 1] * timeSlice;
}

void EnergyEfficientScheduler::run() {
    const double timeSlice = 1.0; // 1ms time quantum
    
    // Sort processes by arrival time
    std::sort(processes.begin(), processes.end(),
              [](const auto& a, const auto& b) { return a->arrivalTime < b->arrivalTime; });

    size_t completed = 0;
    size_t currentIndex = 0;

    while (completed < processes.size()) {
        // Add newly arrived processes to ready queue
        while (currentIndex < processes.size() && 
               processes[currentIndex]->arrivalTime <= currentTime) {
            readyQueue.push(processes[currentIndex]);
            currentIndex++;
        }

        if (!readyQueue.empty()) {
            auto currentProcess = readyQueue.front();
            readyQueue.pop();

            // Adjust frequency based on process characteristics
            adjustFrequency(currentProcess);

            // Execute process for one time slice
            double executionTime = std::min(timeSlice, currentProcess->remainingTime);
            currentProcess->remainingTime -= executionTime;
            
            // Calculate and add energy consumption
            totalEnergyConsumption += calculateEnergyConsumption(currentProcess, executionTime);

            // If process is not finished, put it back in queue
            if (currentProcess->remainingTime > 0) {
                readyQueue.push(currentProcess);
            } else {
                completed++;
                std::cout << "Process " << currentProcess->pid 
                         << " completed at time " << currentTime 
                         << std::endl;
            }
        }
        
        currentTime += timeSlice;
    }
}

double EnergyEfficientScheduler::getTotalEnergyConsumption() const {
    return totalEnergyConsumption;
}
