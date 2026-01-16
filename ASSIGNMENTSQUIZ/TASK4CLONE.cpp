#include <iostream>
#include <queue>
#include <iomanip>
#include <vector>
using namespace std;

struct Process {
    int id;           // Process ID
    float at;         // Arrival Time
    float bt;         // Burst Time (total CPU time needed)
    float remaining_bt; // Remaining Burst Time
    float wt;         // Waiting Time
    float tat;        // Turnaround Time
    float ct;         // Completion Time
};

struct GanttEntry {
    int process_id;   // Process executing
    float start_time; // When process started
    float end_time;   // When process finished this time slice
};

int main() {
    int n = 6;        // Number of processes
    float tq = 25;    // Time Quantum (25 time units per process)
    Process p[6] = {  // Process array with (id, arrival_time, burst_time, remaining, wt, tat, ct)
        {1, 0, 99.99, 99.99, 0, 0, 0},
        {2, 1, 107.9, 107.9, 0, 0, 0},
        {3, 2, 143.77, 143.77, 0, 0, 0},
        {4, 3, 20.24, 20.24, 0, 0, 0},
        {5, 4, 50.55, 50.55, 0, 0, 0},
        {6, 5, 66.66, 66.66, 0, 0, 0}
    };
    
    cout << "Round Robin (RR) Scheduling\n";
    cout << "===========================\n";
    cout << "Time Quantum: " << tq << "\n\n";
    
    vector<GanttEntry> gantt_entries;  // Store execution timeline
    
    queue<int> q;             // Queue to hold ready processes
    float current_time = 0;   // Current system time
    int completed = 0;        // Counter for completed processes
    
    // Main scheduling loop - continues until all processes complete
    while (completed < n) {
        // Add all processes that have arrived to the ready queue
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && p[i].remaining_bt > 0) {  // Check if arrived and not done
                bool already_in_queue = false;
                queue<int> temp = q;
                while (!temp.empty()) {
                    if (temp.front() == i) {
                        already_in_queue = true;  // Found process already in queue
                        break;
                    }
                    temp.pop();
                }
                if (!already_in_queue) {
                    q.push(i);  // Add process to ready queue
                }
            }
        }
        
        if (q.empty()) {
            // No process ready - jump to next arrival time
            for (int i = 0; i < n; i++) {
                if (p[i].remaining_bt > 0 && p[i].at > current_time) {
                    current_time = p[i].at;  // Jump time to next arrival
                    break;
                }
            }
            continue;  // Skip to next iteration
        }
        
        int idx = q.front();  // Get first process from queue
        q.pop();  // Remove it from queue
        
        float start_time = current_time;  // Record start time of execution
        float execute_time = min(p[idx].remaining_bt, tq);  // Execute for min(remaining work, time quantum)
        current_time += execute_time;  // Advance time
        p[idx].remaining_bt -= execute_time;  // Reduce remaining work
        
        gantt_entries.push_back({p[idx].id, start_time, current_time});  // Store execution segment
        
        if (p[idx].remaining_bt > 0) {
            q.push(idx);  // Process not done - return to back of queue
        } else {
            p[idx].ct = current_time;  // Set completion time
            p[idx].tat = p[idx].ct - p[idx].at;  // Calculate turnaround time
            p[idx].wt = p[idx].tat - p[idx].bt;  // Calculate waiting time
            completed++;  // Increment completed counter
        }
    }
    
    // Display process details table
    cout << "Process\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n";
    cout << "-------\t------------\t----------\t------------\t---------------\n";
    
    float avg_wt = 0, avg_tat = 0;  // Initialize sum variables
    for (int i = 0; i < n; i++) {
        cout << "P" << p[i].id << "\t" << fixed << setprecision(2)   // Display process ID and metrics
             << p[i].at << "\t\t" << p[i].bt << "\t\t" 
             << p[i].wt << "\t\t" << p[i].tat << "\n";
        avg_wt += p[i].wt;  // Accumulate waiting times
        avg_tat += p[i].tat;  // Accumulate turnaround times
    }
    
    avg_wt /= n;  // Calculate average waiting time
    avg_tat /= n;  // Calculate average turnaround time
    
    cout << "\n===========================\n";
    cout << "Average Waiting Time (AVEWT): " << fixed << setprecision(2) << avg_wt << "\n";
    cout << "Average Turnaround Time (AVETT): " << avg_tat << "\n";
    
    // Display Gantt Chart
    cout << "\nGantt Chart:\n";
    cout << "============\n";
    
    // Process boxes
    cout << "|";
    for (auto& entry : gantt_entries) {  // Loop through each execution segment
        cout << setw(6) << "P" + to_string(entry.process_id) << "|";  // Print process boxes
    }
    cout << "\n";
    
    // Time line
    cout << setw(1) << " ";
    for (auto& entry : gantt_entries) {
        cout << setw(6) << fixed << setprecision(0) << entry.start_time << "|";  // Print start times
    }
    // Add final time
    cout << setw(6) << fixed << setprecision(0) << gantt_entries.back().end_time << "\n";  // Print end time
    
    // Detailed timeline
    cout << "\nDetailed Timeline:\n";
    cout << "==================\n";
    for (auto& entry : gantt_entries) {
        cout << "P" << entry.process_id << ": " << fixed << setprecision(2)  // Print each execution interval
             << entry.start_time << " - " << entry.end_time << "\n";
    }
    
    return 0;
}
