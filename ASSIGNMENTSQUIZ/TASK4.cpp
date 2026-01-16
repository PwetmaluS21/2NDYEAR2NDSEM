/*4. Round-robin
Same burst time from #3
quantum time: 25
Kelangan may gantt chart
*/

#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
using namespace std;

int main(){
    vector<int> burstTime = {20, 50, 66, 99, 107, 143};
    int n = burstTime.size();
    int timeQuantum = 25;
    vector<int> waitingTime(n, 0);
    vector<int> turnaroundTime(n, 0);
    vector<int> remainingBurstTime = burstTime;

    int time = 0;
    queue<int> processQueue;
    for (int i = 0; i < n; i++) {
        processQueue.push(i);
    }

    while (!processQueue.empty()) {
        int idx = processQueue.front();
        processQueue.pop();

        if (remainingBurstTime[idx] > timeQuantum) {
            time += timeQuantum;
            remainingBurstTime[idx] -= timeQuantum;
            processQueue.push(idx);
        } else {
            time += remainingBurstTime[idx];
            waitingTime[idx] = time - burstTime[idx];
            remainingBurstTime[idx] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
    }

    double totalWaitingTime = 0, totalTurnaroundTime = 0;
    cout << "\n\tPROCESS\t\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n";
    for (int i = 0; i < n; i++) {
        cout << "\tP" << i << "\t\t" << burstTime[i] << "\t\t" << waitingTime[i] << "\t\t" << turnaroundTime[i] << endl;
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time -- " << totalWaitingTime / n;
    cout << "\nAverage Turnaround Time -- " << totalTurnaroundTime / n << endl;

    return 0;
}