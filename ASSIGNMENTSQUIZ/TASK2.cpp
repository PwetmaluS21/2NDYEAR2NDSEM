/* 2. create first come first serve scheduling
there will be 10 processes
Arrival time depends on yourself
Process burst:
9
8
7
8
7
8
2
1
2
5

OUTPUT:
printing of the table
average waiting time
average turnaround time
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main (){
    const int n = 10;
    vector<int> burstTime = {9, 8, 7, 8, 7, 8, 2, 1, 2, 5};
    vector<int> waitingTime(n);
    vector<int> turnaroundTime(n);

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