#include <iostream>
using namespace std;

int main() {
    int n = 10;
    int bt[] = {9, 8, 7, 8, 7, 8, 2, 1, 2, 5}; // Burst times
    int wt[10], tat[10];
    float avg_wt = 0, avg_tat = 0;
    
    cout << "FCFS (First Come First Serve) Scheduling\n";
    cout << "=========================================\n\n";
    
    // Calculate waiting time for each process
    wt[0] = 0; // First process has 0 waiting time
    
    for (int i = 1; i < n; i++) {
        wt[i] = wt[i-1] + bt[i-1];
    }
    
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        tat[i] = wt[i] + bt[i];
    }
    
    // Display process details
    cout << "Process\tBurst Time\tWaiting Time\tTurnaround Time\n";
    cout << "-------\t----------\t------------\t---------------\n";
    
    for (int i = 0; i < n; i++) {
        cout << "P" << i+1 << "\t" << bt[i] << "\t\t" << wt[i] << "\t\t" << tat[i] << "\n";
        avg_wt += wt[i];
        avg_tat += tat[i];
    }
    
    avg_wt /= n;
    avg_tat /= n;
    
    cout << "\n=========================================\n";
    cout << "Average Waiting Time (AVEWT): " << fixed;
    cout.precision(2);
    cout << avg_wt << "\n";
    cout << "Average Turnaround Time (AVETT): " << avg_tat << "\n";
    
    // Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "|";
    for (int i = 0; i < n; i++) {
        cout << " P" << i+1 << " |";
    }
    cout << "\n";
    
    cout << "0";
    int time = 0;
    for (int i = 0; i < n; i++) {
        time += bt[i];
        cout << "    " << time;
    }
    cout << "\n";
    
    return 0;
}
