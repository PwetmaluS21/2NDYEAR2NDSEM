ey Components
1. Struct Definition
struct Process {
    int id;      // Process ID
    float bt;    // Burst Time (CPU time needed)
    float wt;    // Waiting Time
    float tat;   // Turnaround Time
};
Simpler than Round Robin since SJF doesn't need arrival times or remaining burst time (non-preemptive).

2. Comparison Function
bool compare(Process a, Process b) {
    return a.bt < b.bt;  // Returns true if a's burst time < b's burst time
}
Used to sort processes by burst time in ascending order.

3. Process Data
int n = 6;  // 6 processes
Process p[6] = {
    {1, 99.99, 0, 0},
    {2, 107.9, 0, 0},
    // ... etc
};
Six processes with different burst times (no arrival times since this is non-preemptive).

4. Main Algorithm
sort(p, p + n, compare);
Step 1: Sort by Burst Time
Arranges processes from shortest to longest burst time.

Example: If original burst times are [99.99, 107.9, 143.77, 20.24, 50.55, 66.66]
After sorting: [20.24, 50.55, 66.66, 99.99, 107.9, 143.77] (P4, P5, P6, P1, P2, P3)

Step 2: Calculate Waiting Time
p[0].wt = 0;  // First process waits 0 time
for (int i = 1; i < n; i++) {
    p[i].wt = p[i-1].wt + p[i-1].bt;
}
Logic:

First process (shortest): waits 0 time (starts immediately)
Second process: waits for first process to complete = 20.24
Third process: waits for first + second = 20.24 + 50.55 = 70.79
And so on...
Step 3: Calculate Turnaround Time
for (int i = 0; i < n; i++) {
    p[i].tat = p[i].wt + p[i].bt;
}
Turnaround Time = Waiting Time + Burst Time

Example for P4 (id=4, bt=20.24):

Waiting Time = 0
Turnaround Time = 0 + 20.24 = 20.24
5. Output Section
Process Details Table
Displays each process with:

Process ID
Burst Time
Waiting Time
Turnaround Time

Average Calculations
avg_wt /= n;   // Sum of all waiting times / number of processes
avg_tat /= n;  // Sum of all turnaround times / number of processes
These metrics show how efficient the scheduling is.

Gantt Chart
cout << "|";
for (int i = 0; i < n; i++) {
    cout << " P" << p[i].id << " |";
}
cout << "\n";

cout << "0";
float time = 0;
for (int i = 0; i < n; i++) {
    time += p[i].bt;
    cout << "   " << time;
}
Displays visual timeline showing:

Which process executes in which order
Time markers showing when each process completes
Example Output:

Execution Example
With the given burst times:

Process	Burst Time	Waiting Time	Turnaround Time
P4	20.24	0	20.24
P5	50.55	20.24	70.79
P6	66.66	70.79	137.45
P1	99.99	137.45	237.44
P2	107.9	237.44	345.34
P3	143.77	345.34	489.11
Average WT: Sum of all WT / 6
Average TAT: Sum of all TAT / 6

Purpose
This program demonstrates SJF scheduling by:

Sorting processes by burst time (shortest first)
Calculating waiting and turnaround times
Computing scheduling efficiency averages
Visualizing execution order with a Gantt chart