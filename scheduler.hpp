#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <vector>
#include <queue>
#include <memory>
#include <chrono>

struct Process {
    int pid;
    int priority;
    double burstTime;
    double remainingTime;
    double arrivalTime;
    int frequencyLevel;  // CPU frequency level (1-5, where 5 is highest)
    
    Process(int id, double burst, double arrival, int priority = 1)
        : pid(id), burstTime(burst), remainingTime(burst),
          arrivalTime(arrival), priority(priority), frequencyLevel(3) {}
};

class EnergyEfficientScheduler {
private:
    std::vector<std::shared_ptr<Process>> processes;
    std::queue<std::shared_ptr<Process>> readyQueue;
    double currentTime;
    double totalEnergyConsumption;
    
    // Frequency levels and their power consumption (watts)
    const std::vector<double> frequencyLevels = {1.0, 1.5, 2.0, 2.5, 3.0};
    const std::vector<double> powerConsumption = {10, 15, 25, 35, 50};

public:
    EnergyEfficientScheduler();
    void addProcess(std::shared_ptr<Process> process);
    void run();
    double getTotalEnergyConsumption() const;
    void adjustFrequency(std::shared_ptr<Process> process);
    double calculateEnergyConsumption(std::shared_ptr<Process> process, double timeSlice) const;
};

#endif
