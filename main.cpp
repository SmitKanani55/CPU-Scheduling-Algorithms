#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

struct Process {
    int pid;
    int arrivalTime;
    int burstTime;
    int priority;
    int startTime;
    int completionTime;
    int turnaroundTime;
    int waitingTime;
    int remainingTime;
};

// Global variables to track performance
float avgTAT_FCFS = 0, avgTAT_SJF = 0, avgTAT_PRIORITY = 0, avgTAT_RR = 0;

// ---------- Utility Functions ----------
float calculateAndPrintAverages(vector<Process> processes, const string &algorithmName) {
    if (processes.empty()) {
        cout << "No processes to schedule.\n";
        return 0.0f;
    }

    float totalTurnaroundTime = 0;
    float totalWaitingTime = 0;
    int totalIdleTime = 0;
    int lastCompletionTime = 0;
    int firstArrivalTime = processes[0].arrivalTime;
    int numProcesses = processes.size();

    cout << "\n--- " << algorithmName << " Results ---\n";
    for (size_t i = 0; i < processes.size(); i++) {
        Process p = processes[i];
        cout << "Process " << p.pid
             << " | Arrival: " << p.arrivalTime
             << " | Burst: " << p.burstTime
             << " | Priority: " << p.priority
             << " | Completion: " << p.completionTime
             << " | Turnaround: " << p.turnaroundTime
             << " | Waiting: " << p.waitingTime << "\n";

        totalTurnaroundTime += p.turnaroundTime;
        totalWaitingTime += p.waitingTime;

        if (p.startTime > lastCompletionTime) {
            totalIdleTime += p.startTime - lastCompletionTime;
        }
        lastCompletionTime = p.completionTime;
    }

    float avgTurnaroundTime = totalTurnaroundTime / numProcesses;
    float avgWaitingTime = totalWaitingTime / numProcesses;
    float totalExecutionTime = lastCompletionTime - firstArrivalTime;
    float cpuUtilization = ((totalExecutionTime - totalIdleTime) / totalExecutionTime) * 100.0f;

    cout << "\nAverage Turnaround Time: " << avgTurnaroundTime
         << "\nAverage Waiting Time: " << avgWaitingTime
         << "\nCPU Utilization: " << cpuUtilization << "%\n";

    return avgTurnaroundTime; // Return for comparison
}

// ---------- Comparison Functions ----------
bool cmpArrival(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

bool cmpPID(const Process &a, const Process &b) {
    return a.pid < b.pid;
}

// ---------- Scheduling Algorithms ----------
void firstComeFirstServe(vector<Process> processes) {
    sort(processes.begin(), processes.end(), cmpArrival);
    int currentTime = 0;

    for (size_t i = 0; i < processes.size(); i++) {
        if (currentTime < processes[i].arrivalTime)
            currentTime = processes[i].arrivalTime;
        processes[i].startTime = currentTime;
        processes[i].completionTime = currentTime + processes[i].burstTime;
        processes[i].turnaroundTime = processes[i].completionTime - processes[i].arrivalTime;
        processes[i].waitingTime = processes[i].turnaroundTime - processes[i].burstTime;
        currentTime = processes[i].completionTime;
    }

    avgTAT_FCFS = calculateAndPrintAverages(processes, "First-Come First-Served (FCFS)");
}

void shortestJobFirst(vector<Process> processes) {
    int n = processes.size();
    vector<Process> completed;
    vector<bool> done(n, false);
    int currentTime = 0, finished = 0;

    while (finished < n) {
        int idx = -1, minBurst = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrivalTime <= currentTime) {
                if (processes[i].burstTime < minBurst) {
                    minBurst = processes[i].burstTime;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currentTime++;
        } else {
            processes[idx].startTime = currentTime;
            processes[idx].completionTime = currentTime + processes[idx].burstTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            currentTime = processes[idx].completionTime;
            done[idx] = true;
            completed.push_back(processes[idx]);
            finished++;
        }
    }

    sort(completed.begin(), completed.end(), cmpPID);
    avgTAT_SJF = calculateAndPrintAverages(completed, "Shortest Job First (SJF)");
}

void priorityScheduling(vector<Process> processes) {
    int n = processes.size();
    vector<Process> completed;
    vector<bool> done(n, false);
    int currentTime = 0, finished = 0;

    while (finished < n) {
        int idx = -1, bestPriority = INT_MAX;
        for (int i = 0; i < n; i++) {
            if (!done[i] && processes[i].arrivalTime <= currentTime) {
                if (processes[i].priority < bestPriority) {
                    bestPriority = processes[i].priority;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            currentTime++;
        } else {
            processes[idx].startTime = currentTime;
            processes[idx].completionTime = currentTime + processes[idx].burstTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            currentTime = processes[idx].completionTime;
            done[idx] = true;
            completed.push_back(processes[idx]);
            finished++;
        }
    }

    sort(completed.begin(), completed.end(), cmpPID);
    avgTAT_PRIORITY = calculateAndPrintAverages(completed, "Priority Scheduling");
}

void roundRobin(vector<Process> processes, int quantum) {
    int n = processes.size();
    vector<Process> completed;
    queue<int> ready;
    sort(processes.begin(), processes.end(), cmpArrival);

    for (int i = 0; i < n; i++)
        processes[i].remainingTime = processes[i].burstTime;

    int currentTime = 0, finished = 0, nextArrival = 0;
    while (nextArrival < n && processes[nextArrival].arrivalTime <= currentTime)
        ready.push(nextArrival++);

    while (finished < n) {
        if (ready.empty()) {
            currentTime++;
            while (nextArrival < n && processes[nextArrival].arrivalTime <= currentTime)
                ready.push(nextArrival++);
            continue;
        }

        int idx = ready.front();
        ready.pop();

        if (processes[idx].remainingTime == processes[idx].burstTime)
            processes[idx].startTime = currentTime;

        int execTime = min(quantum, processes[idx].remainingTime);
        currentTime += execTime;
        processes[idx].remainingTime -= execTime;

        while (nextArrival < n && processes[nextArrival].arrivalTime <= currentTime)
            ready.push(nextArrival++);

        if (processes[idx].remainingTime == 0) {
            processes[idx].completionTime = currentTime;
            processes[idx].turnaroundTime = processes[idx].completionTime - processes[idx].arrivalTime;
            processes[idx].waitingTime = processes[idx].turnaroundTime - processes[idx].burstTime;
            completed.push_back(processes[idx]);
            finished++;
        } else {
            ready.push(idx);
        }
    }

    sort(completed.begin(), completed.end(), cmpPID);
    avgTAT_RR = calculateAndPrintAverages(completed, "Round Robin");
}

// ---------- Main ----------
int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    cout << "Enter Arrival Time, Burst Time, Priority:\n";
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "P" << i+1 << ": ";
        cin >> processes[i].arrivalTime >> processes[i].burstTime >> processes[i].priority;
    }

    firstComeFirstServe(processes);
    shortestJobFirst(processes);
    priorityScheduling(processes);

    int q;
    cout << "\nEnter Quantum for Round Robin: ";
    cin >> q;
    roundRobin(processes, q);

    // Best algorithm selection
    float bestTAT = avgTAT_FCFS;
    string bestAlgo = "First-Come First-Served (FCFS)";

    if (avgTAT_SJF < bestTAT) { bestTAT = avgTAT_SJF; bestAlgo = "Shortest Job First (SJF)"; }
    if (avgTAT_PRIORITY < bestTAT) { bestTAT = avgTAT_PRIORITY; bestAlgo = "Priority Scheduling"; }
    if (avgTAT_RR < bestTAT) { bestTAT = avgTAT_RR; bestAlgo = "Round Robin"; }

    cout << "\n>>> Best suited algorithm based on Average Turnaround Time: " << bestAlgo << " <<<\n";

    return 0;
}
