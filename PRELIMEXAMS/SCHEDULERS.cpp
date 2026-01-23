#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include <numeric>
#include <queue>
#include <climits>

using namespace std;

// Structure to hold process information
struct Process {
    int PID;
    int AT;      // Arrival Time
    int BT;      // Burst Time
    int CT;      // Completion Time
    int WT;      // Waiting Time
    int TAT;     // Turnaround Time
    int remainingBT;  // For SRTF
};

// Function prototypes
vector<Process> ShortestJobFirst(vector<Process> processes);
vector<Process> ShortestRemainingTimeFirst(vector<Process> processes);
vector<Process> RoundRobin(vector<Process> processes, int timeQuantum);
double CalculateRecommendedTimeQuantum(vector<int> burstTimes, string method);
void DisplayTable(const vector<Process>& processes, const string& algorithmName);
void DisplayStatistics(const vector<Process>& processes);

// ============ SHORTEST JOB FIRST (SJF) ============
vector<Process> ShortestJobFirst(vector<Process> processes) {
    vector<Process> result = processes;
    vector<bool> completed(result.size(), false);
    int currentTime = 0;
    int completedCount = 0;

    while (completedCount < result.size()) {
        int shortestIdx = -1;
        int shortestBT = INT_MAX;

        // Find the process with shortest burst time that has arrived
        for (int i = 0; i < result.size(); i++) {
            if (!completed[i] && result[i].AT <= currentTime && result[i].BT < shortestBT) {
                shortestBT = result[i].BT;
                shortestIdx = i;
            }
        }

        // If no process found, move time forward
        if (shortestIdx == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < result.size(); i++) {
                if (!completed[i]) {
                    nextArrival = min(nextArrival, result[i].AT);
                }
            }
            currentTime = nextArrival;
            continue;
        }

        // Execute the process
        currentTime += result[shortestIdx].BT;
        result[shortestIdx].CT = currentTime;
        result[shortestIdx].TAT = result[shortestIdx].CT - result[shortestIdx].AT;
        result[shortestIdx].WT = result[shortestIdx].TAT - result[shortestIdx].BT;
        completed[shortestIdx] = true;
        completedCount++;
    }

    return result;
}

// ============ SHORTEST REMAINING TIME FIRST (SRTF) ============
vector<Process> ShortestRemainingTimeFirst(vector<Process> processes) {
    vector<Process> result = processes;
    for (auto& p : result) {
        p.remainingBT = p.BT;
    }

    int currentTime = 0;
    int completedCount = 0;
    int n = result.size();

    while (completedCount < n) {
        // Find process with shortest remaining burst time that has arrived
        int shortestIdx = -1;
        int shortestRemaining = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (result[i].remainingBT > 0 && result[i].AT <= currentTime && result[i].remainingBT < shortestRemaining) {
                shortestRemaining = result[i].remainingBT;
                shortestIdx = i;
            }
        }

        // If no process found, move time forward to next arrival
        if (shortestIdx == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (result[i].remainingBT > 0) {
                    nextArrival = min(nextArrival, result[i].AT);
                }
            }
            if (nextArrival != INT_MAX) {
                currentTime = nextArrival;
            }
            continue;
        }

        // Execute the selected process for 1 unit time
        result[shortestIdx].remainingBT--;
        currentTime++;

        // Check if process is completed
        if (result[shortestIdx].remainingBT == 0) {
            result[shortestIdx].CT = currentTime;
            result[shortestIdx].TAT = result[shortestIdx].CT - result[shortestIdx].AT;
            result[shortestIdx].WT = result[shortestIdx].TAT - result[shortestIdx].BT;
            completedCount++;
        }
    }

    return result;
}

// ============ ROUND ROBIN ============
vector<Process> RoundRobin(vector<Process> processes, int timeQuantum) {
    vector<Process> result = processes;
    for (auto& p : result) {
        p.remainingBT = p.BT;
    }

    queue<int> readyQueue;
    int currentTime = 0;
    int completedCount = 0;
    int n = result.size();

    // Add initial processes
    for (int i = 0; i < n; i++) {
        if (result[i].AT == 0) {
            readyQueue.push(i);
        }
    }

    while (completedCount < n || !readyQueue.empty()) {
        if (readyQueue.empty()) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (result[i].remainingBT > 0) {
                    nextArrival = min(nextArrival, result[i].AT);
                }
            }
            currentTime = nextArrival;
            for (int i = 0; i < n; i++) {
                if (result[i].AT == currentTime && result[i].remainingBT > 0) {
                    readyQueue.push(i);
                }
            }
            continue;
        }

        int idx = readyQueue.front();
        readyQueue.pop();

        int timeToRun = min(timeQuantum, result[idx].remainingBT);
        currentTime += timeToRun;
        result[idx].remainingBT -= timeToRun;

        // Add newly arrived processes
        for (int i = 0; i < n; i++) {
            if (result[i].AT <= currentTime && result[i].remainingBT > 0 && i != idx) {
                bool inQueue = false;
                queue<int> tempQueue = readyQueue;
                while (!tempQueue.empty()) {
                    if (tempQueue.front() == i) inQueue = true;
                    tempQueue.pop();
                }
                if (!inQueue && result[i].remainingBT > 0) {
                    readyQueue.push(i);
                }
            }
        }

        if (result[idx].remainingBT == 0) {
            result[idx].CT = currentTime;
            result[idx].TAT = result[idx].CT - result[idx].AT;
            result[idx].WT = result[idx].TAT - result[idx].BT;
            completedCount++;
        } else {
            readyQueue.push(idx);
        }
    }

    return result;
}

// ============ CALCULATE RECOMMENDED TIME QUANTUM ============
double CalculateRecommendedTimeQuantum(vector<int> burstTimes, string method) {
    if (burstTimes.empty()) return 0;

    if (method == "mean" || method == "MEAN") {
        double sum = accumulate(burstTimes.begin(), burstTimes.end(), 0.0);
        return sum / burstTimes.size();
    } else if (method == "median" || method == "MEDIAN") {
        sort(burstTimes.begin(), burstTimes.end());
        int n = burstTimes.size();
        if (n % 2 == 0) {
            return (burstTimes[n / 2 - 1] + burstTimes[n / 2]) / 2.0;
        } else {
            return burstTimes[n / 2];
        }
    }
    return 0;
}

// ============ DISPLAY TABLE ============
void DisplayTable(const vector<Process>& processes, const string& algorithmName) {
    cout << "\n" << string(100, '=') << endl;
    cout << "ALGORITHM: " << algorithmName << endl;
    cout << string(100, '=') << endl;

    cout << left << setw(10) << "PID" 
         << setw(10) << "AT" 
         << setw(10) << "BT" 
         << setw(10) << "CT" 
         << setw(10) << "TAT" 
         << setw(10) << "WT" << endl;
    cout << string(60, '-') << endl;

    for (const auto& p : processes) {
        cout << left << setw(10) << p.PID 
             << setw(10) << p.AT 
             << setw(10) << p.BT 
             << setw(10) << p.CT 
             << setw(10) << p.TAT 
             << setw(10) << p.WT << endl;
    }
}

// ============ DISPLAY STATISTICS ============
void DisplayStatistics(const vector<Process>& processes) {
    double totalTAT = 0, totalWT = 0;

    for (const auto& p : processes) {
        totalTAT += p.TAT;
        totalWT += p.WT;
    }

    double aveTAT = totalTAT / processes.size();
    double aveWT = totalWT / processes.size();

    cout << "\nAVE_TAT (Average Turnaround Time): " << fixed << setprecision(2) << aveTAT << endl;
    cout << "AVE_WT (Average Waiting Time): " << fixed << setprecision(2) << aveWT << endl;
    cout << string(100, '=') << endl;
}

// ============ MAIN FUNCTION ============
int main() {
    // Initialize data
    vector<int> PID = {1, 2, 3, 4, 5, 6, 7, 8};
    vector<int> AT = {1, 3, 8, 4, 6, 7, 2, 5};
    vector<int> BT = {53, 43, 18, 16, 24, 73, 99, 27};

    // Create process vector
    vector<Process> processes;
    for (int i = 0; i < PID.size(); i++) {
        processes.push_back({PID[i], AT[i], BT[i], 0, 0, 0, 0});
    }

    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║                CPU SCHEDULING ALGORITHMS               ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;

    // Display input data
    cout << "\nINPUT DATA:" << endl;
    cout << string(60, '-') << endl;
    cout << left << setw(10) << "PID" << setw(15) << "AT" << setw(15) << "BT" << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < PID.size(); i++) {
        cout << left << setw(10) << PID[i] << setw(15) << AT[i] << setw(15) << BT[i] << endl;
    }

    // Calculate statistics for time quantum
    cout << "\n" << string(100, '=') << endl;
    cout << "TIME QUANTUM CALCULATIONS:" << endl;
    cout << string(100, '=') << endl;

    double meanBT = CalculateRecommendedTimeQuantum(BT, "mean");
    double medianBT = CalculateRecommendedTimeQuantum(BT, "median");

    cout << fixed << setprecision(2);
    cout << "\nAVE BT (Mean of Burst Times): " << meanBT << endl;
    cout << "MEDIAN BT (Median of Burst Times): " << medianBT << endl;

    // ============ SHORTEST JOB FIRST ============
    cout << "\n" << string(100, '=') << endl;
    cout << "1. SHORTEST JOB FIRST (SJF)" << endl;
    vector<Process> sjfResult = ShortestJobFirst(processes);
    DisplayTable(sjfResult, "Shortest Job First");
    DisplayStatistics(sjfResult);

    // ============ SHORTEST REMAINING TIME FIRST ============
    cout << "\n" << string(100, '=') << endl;
    cout << "2. SHORTEST REMAINING TIME FIRST (SRTF)" << endl;
    vector<Process> srtfResult = ShortestRemainingTimeFirst(processes);
    DisplayTable(srtfResult, "Shortest Remaining Time First");
    DisplayStatistics(srtfResult);

    // ============ ROUND ROBIN (with Mean) ============
    cout << "\n" << string(100, '=') << endl;
    cout << "3. ROUND ROBIN (Time Quantum = Mean BT)" << endl;
    int timeQuantumMean = (int)round(meanBT);
    cout << "Time Quantum (TQ): " << timeQuantumMean << endl;
    vector<Process> rrMeanResult = RoundRobin(processes, timeQuantumMean);
    DisplayTable(rrMeanResult, "Round Robin (Mean TQ)");
    DisplayStatistics(rrMeanResult);

    // ============ SUMMARY COMPARISON ============
    cout << "\n" << string(100, '=') << endl;
    cout << "SUMMARY COMPARISON OF ALL ALGORITHMS" << endl;
    cout << string(100, '=') << endl;

    double sjfAveTAT = 0, sjfAveWT = 0;
    double srtfAveTAT = 0, srtfAveWT = 0;
    double rrMeanAveTAT = 0, rrMeanAveWT = 0;

    for (const auto& p : sjfResult) {
        sjfAveTAT += p.TAT;
        sjfAveWT += p.WT;
    }
    for (const auto& p : srtfResult) {
        srtfAveTAT += p.TAT;
        srtfAveWT += p.WT;
    }
    for (const auto& p : rrMeanResult) {
        rrMeanAveTAT += p.TAT;
        rrMeanAveWT += p.WT;
    }

    int n = processes.size();
    sjfAveTAT /= n;
    sjfAveWT /= n;
    srtfAveTAT /= n;
    srtfAveWT /= n;
    rrMeanAveTAT /= n;
    rrMeanAveWT /= n;

    cout << left << setw(35) << "Algorithm" 
         << setw(25) << "AVE_TAT" 
         << setw(25) << "AVE_WT" << endl;
    cout << string(85, '-') << endl;
    cout << left << setw(35) << "Shortest Job First (SJF)" 
         << fixed << setprecision(2) << setw(25) << sjfAveTAT 
         << setw(25) << sjfAveWT << endl;
    cout << left << setw(35) << "Shortest Remaining Time First (SRTF)" 
         << fixed << setprecision(2) << setw(25) << srtfAveTAT 
         << setw(25) << srtfAveWT << endl;
    cout << left << setw(35) << "Round Robin (Mean TQ = " + to_string(timeQuantumMean) + ")" 
         << fixed << setprecision(2) << setw(25) << rrMeanAveTAT 
         << setw(25) << rrMeanAveWT << endl;
    cout << string(100, '=') << endl;

    cout << "\n✓ All functions executed successfully!" << endl;

    return 0;
}
