/* 3. Shortest job first
6 elements
- burst time
99.99
107.9
143.77
20.24
50.55
66.66*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main() {
    const int n = 6;
    vector<double> burstTime = {99.99, 107.9, 143.77, 20.24, 50.55, 66.66};
    vector<double> waitingTime(n);
    vector<double> turnaroundTime(n);

    // Sort burst times for SJF
    sort(burstTime.begin(), burstTime.end());

    // Calculate waiting time
    waitingTime[0] = 0;
    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i - 1] + burstTime[i - 1];
    }

    // Calculate turnaround time
    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
    }

    // Calculate average waiting time and turnaround time
    double avgWaitingTime = accumulate(waitingTime.begin(), waitingTime.end(), 0.0) / n;
    double avgTurnaroundTime = accumulate(turnaroundTime.begin(), turnaroundTime.end(), 0.0) / n;

    // Print the table
    cout << "\n\t PROCESS \tBURST TIME \t WAITING TIME\t TURNAROUND TIME\n";
    for (int i = 0; i < n; i++) {
        cout << "\n\t P" << i << " \t\t " << burstTime[i] << " \t\t " << waitingTime[i] << " \t\t " << turnaroundTime[i];
    }
    cout << "\nAverage Waiting Time -- " << avgWaitingTime;
    cout << "\nAverage Turnaround Time -- " << avgTurnaroundTime << endl;

    return 0;
}