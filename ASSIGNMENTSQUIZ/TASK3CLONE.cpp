#include <iostream>
#include <algorithm>  // For sorting function
using namespace std;

struct Process {
    int id;      // Process ID
    float bt;    // Burst Time (CPU time needed)
    float wt;    // Waiting Time
    float tat;   // Turnaround Time
};

// Comparison function to sort processes by burst time (ascending)
bool compare(Process a, Process b) {
    return a.bt < b.bt;  // Return true if a's burst time < b's burst time
}

int main() {
    int n = 6;  // Number of processes
    Process p[6] = {  // Process array with (id, burst_time, wt, tat)
        {1, 99.99, 0, 0},
        {2, 107.9, 0, 0},
        {3, 143.77, 0, 0},
        {4, 20.24, 0, 0},
        {5, 50.55, 0, 0},
        {6, 66.66, 0, 0}
    };
    
    cout << "SJF (Shortest Job First) Scheduling\n";
    cout << "====================================\n\n";
    
    sort(p, p + n, compare);  // Sort processes by burst time (ascending order)
    
    p[0].wt = 0;  // First process waits 0 time
    for (int i = 1; i < n; i++) {
        p[i].wt = p[i-1].wt + p[i-1].bt;  // WT = previous WT + previous BT
    }
    
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].wt + p[i].bt;  // TAT = Waiting Time + Burst Time
    }
    
    float avg_wt = 0, avg_tat = 0;  // Initialize sum variables
    
    // Display process details
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    cout << "-------\t----------\t------------\t---------------\n";
    
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" << p[i].bt << "\t\t" << p[i].wt << "\t\t" << p[i].tat << "\n";  // Display process metrics
        avg_wt += p[i].wt;  // Accumulate waiting times
        avg_tat += p[i].tat;  // Accumulate turnaround times
    }
    
    avg_wt /= n;  // Calculate average waiting time
    avg_tat /= n;  // Calculate average turnaround time
    
    cout << "\n====================================\n";
    cout << "Average Waiting Time (AVEWT): " << fixed;
    cout.precision(2);  // Set precision to 2 decimal places
    cout << avg_wt << "\n";
    cout << "Average Turnaround Time (AVETT): " << avg_tat << "\n";
    
    cout << "\nGantt Chart:\n";
    cout << "|";
    for (int i = 0; i < n; i++) {
        cout << " P" << p[i].id << " |";  // Print process boxes in sorted order
    }
    cout << "\n";
    
    cout << "0";  // Print start time
    float time = 0;  // Track cumulative time
    for (int i = 0; i < n; i++) {
        time += p[i].bt;  // Add burst time to get completion time
        cout << "   " << time;  // Print completion time for each process
    }
    cout << "\n";
    
    return 0;
}
