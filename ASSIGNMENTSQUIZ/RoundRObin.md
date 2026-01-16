Code Explanation: Round Robin Scheduling Simulator
This C++ program implements a Round Robin (RR) CPU scheduling algorithm, which is a commonly used scheduling technique in operating systems.

Overview
Round Robin is a preemptive scheduling algorithm where each process gets a fixed time slice (called time quantum) to execute. If a process doesn't complete within that time, it's moved to the back of the queue and the next process executes.

Key Components
1. Struct Definitions
These define the data structures for processes and for tracking the execution timeline (Gantt chart).

2. Process Data
The program simulates 6 processes with different arrival times and burst times (work required).

3. Main Algorithm: Round Robin Scheduling
The algorithm uses a queue to manage process execution:

Algorithm Steps:
Loop until all processes complete:

Add Arrived Processes to Queue

Checks which processes have arrived (arrival time ≤ current time)
Only adds processes that haven't been added yet
Avoids duplicates in the queue
Handle Empty Queue

If no process is ready, jump to the next arrival time
This prevents idle waiting
Execute Process

Handle Process After Time Slice

If process still has work remaining → add it back to queue
If process is complete → calculate metrics:
Completion Time (CT) = when it finishes
Turnaround Time (TAT) = CT - Arrival Time
Waiting Time (WT) = TAT - Burst Time
Record Gantt Chart Entry

Tracks which process ran and during which time period
4. Output Section
Process Details Table
Displays metrics for each process.

Average Calculations
Gantt Chart Display
Shows a visual timeline:

This helps visualize which process was executing at each time period.

Example Execution Flow
With time quantum = 25:

Time 0: P1 arrives, executes 25 units (remaining: 74.99)
Time 25: P1 goes to back of queue, P2 executes 25 units (remaining: 82.9)
Time 50: P2 goes to back of queue, continues...
Each process gets fair CPU time in round-robin fashion.

Purpose
This program helps understand and visualize how Round Robin scheduling works by:

Simulating CPU scheduling
Calculating waiting and turnaround times
Displaying a Gantt chart showing execution order
Computing averages to measure scheduling efficiency