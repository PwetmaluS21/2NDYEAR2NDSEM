#include <iostream>
using namespace std;

int main() {
    int n = 10; 
    int bt[] = {9, 8, 7, 8, 7, 8, 2, 1, 2, 5}; 
    int at[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int wt[10], tat[10], ct[10];
    float avg_wt = 0, avg_tat = 0; 
    
    cout << "FCFS (First Come First Serve) Scheduling\n";
    cout << "=========================================\n\n";
    
    ct[0] = at[0] + bt[0];
    wt[0] = 0;
    
    for (int i = 1; i < n; i++) {
        ct[i] = ct[i-1] + bt[i];  // CT = previous CT + current BT
        wt[i] = ct[i-1] - at[i];  // WT = previous CT - current AT
        if (wt[i] < 0) wt[i] = 0;  // If process arrives after previous finishes, no wait
    }
    
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];  // TAT = Completion Time - Arrival Time
    }
    
    // Display process table
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    cout << "-------\t------------\t----------\t------------\t---------------\n";
    
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" << at[i] << "\t\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << "\n";  // Display all metrics for each process
        avg_wt += wt[i];  // Accumulate waiting times
        avg_tat += tat[i];  // Accumulate turnaround times
    }
    
    avg_wt /= n;  // Calculate average waiting time
    avg_tat /= n;  // Calculate average turnaround time
    
    cout << "\n=========================================\n";
    cout << "Average Waiting Time (AVEWT): " << fixed;
    cout.precision(2);  // Set precision to 2 decimal places
    cout << avg_wt << "\n";
    cout << "Average Turnaround Time (AVETT): " << avg_tat << "\n";
    
    cout << "\nGantt Chart:\n";
    cout << "|";
    for (int i = 0; i < n; i++) {
        cout << " P" << i+1 << " |";  // Print process boxes in FCFS order
    }
    cout << "\n";
    
    cout << at[0];  // Print start time (arrival of first process)
    for (int i = 0; i < n; i++) {
        cout << "    " << ct[i];  // Print completion time for each process
    }
    cout << "\n";
    
    return 0;
}