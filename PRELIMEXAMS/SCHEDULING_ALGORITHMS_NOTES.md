# CPU SCHEDULING ALGORITHMS - COMPREHENSIVE NOTES

## Overview
CPU Scheduling is the process of selecting processes to execute on the CPU. Different scheduling algorithms optimize for different criteria such as minimizing waiting time, turnaround time, or maximizing CPU utilization.

---

## 1. SHORTEST JOB FIRST (SJF)

### Definition
SJF is a **non-preemptive** scheduling algorithm that selects the process with the smallest burst time (CPU time) among all ready processes.

### Characteristics
- **Type**: Non-preemptive (process runs to completion without interruption)
- **Decision Point**: Made when CPU is idle or a process completes
- **Criteria**: Select process with minimum burst time
- **Optimal**: Minimizes average waiting time among non-preemptive algorithms

### Algorithm Steps
1. When CPU becomes free, examine all processes that have arrived
2. Select the process with the smallest burst time
3. Execute it completely without interruption
4. Repeat until all processes are completed

### Advantages
✓ Minimizes average waiting time
✓ Simple to implement
✓ Good for batch processing

### Disadvantages
✗ Cannot respond to new arrivals mid-execution
✗ Long processes suffer starvation (may wait very long)
✗ Requires knowledge of burst time in advance

### Example Results (from program)
```
AVE_TAT (Average Turnaround Time): 152.25
AVE_WT (Average Waiting Time): 108.12
```

### Execution Trace
```
Time 1: P1 executes (BT=53) → completes at 54
Time 54: P7 executes (BT=99) → completes at 153
(and so on...)
```

---

## 2. SHORTEST REMAINING TIME FIRST (SRTF)

### Definition
SRTF is the **preemptive version** of SJF. It selects the process with the smallest remaining burst time, allowing interruption when a shorter process arrives.

### Characteristics
- **Type**: Preemptive (can interrupt running process)
- **Decision Point**: Made at every time unit
- **Criteria**: Select process with minimum remaining burst time
- **Optimal**: Best average waiting time among all scheduling algorithms
- **Interruptions**: YES - supports context switching

### Algorithm Steps
1. At each time unit, check all ready processes
2. Select the process with the **shortest remaining burst time**
3. Execute it for 1 unit of time
4. If a new process arrives with shorter burst time → **PREEMPT** current process
5. Repeat until all processes complete

### Advantages
✓ Optimal - minimizes average waiting and turnaround time
✓ Responds to new process arrivals
✓ Better than SJF due to preemption capability
✓ Prevents starvation better

### Disadvantages
✗ Requires preemption mechanism (context switching overhead)
✗ Requires knowing burst times in advance
✗ Context switching has performance cost
✗ May cause process fragmentation

### Key Differences from SJF
| Feature | SJF | SRTF |
|---------|-----|------|
| Preemption | No | **YES** |
| Reselection | Only when process ends | **Every time unit** |
| Decision Point | When CPU idle | **Continuous** |
| Avg Wait Time | Higher | **Lower** |
| Avg TAT | Higher | **Lower** |

### Example Results (from program)
```
AVE_TAT (Average Turnaround Time): 136.88
AVE_WT (Average Waiting Time): 92.75

INTERRUPTIONS DETECTED:
- Time 3: P1 interrupted by P2 (51 remaining > 43 remaining)
- Time 4: P2 interrupted by P4 (42 remaining > 16 remaining)
```

### Execution Trace with Interruptions
```
Time 1: SELECT P1 (remaining=53)
Time 3: INTERRUPT P1 (remaining=51), SELECT P2 (remaining=43)
Time 4: INTERRUPT P2 (remaining=42), SELECT P4 (remaining=16)
Time 20: P4 COMPLETES (CT=20, TAT=16, WT=0)
Time 20: SELECT P3 (remaining=18)
...
```

### Why SRTF Performs Better
- **Earlier completion** of shorter jobs reduces their waiting time significantly
- **Shorter jobs** don't wait behind longer jobs
- **Reduced convoy effect** (long process blocking all others)
- **Better responsiveness** to new arrivals

---

## 3. ROUND ROBIN (RR)

### Definition
Round Robin is a **preemptive** scheduling algorithm that allocates a fixed time slice (time quantum) to each process in turn, cycling through the ready queue.

### Characteristics
- **Type**: Preemptive with time quantum
- **Time Quantum (TQ)**: Fixed time slice per process execution
- **Decision Point**: When time quantum expires or process completes
- **Queue**: Circular (FIFO) queue of ready processes
- **Fairness**: All processes get equal CPU time

### Algorithm Steps
1. Set a fixed time quantum (e.g., 44 milliseconds)
2. Add all arrived processes to ready queue
3. Select first process from queue
4. Execute for **minimum(time quantum, remaining burst time)**
5. If process not complete:
   - Add it to back of queue
   - Move to next process
6. If process complete:
   - Calculate CT, TAT, WT
   - Move to next process
7. Repeat until queue is empty

### Advantages
✓ Fair allocation of CPU time
✓ Good for time-sharing systems
✓ Responsive (no process starves)
✓ Suitable for interactive systems
✓ No need to know burst times in advance
✓ Better than FCFS for average response time

### Disadvantages
✗ Context switching overhead (depends on TQ)
✗ Larger average waiting time than SRTF/SJF
✗ Choice of time quantum is critical
✗ Too small TQ → many context switches
✗ Too large TQ → behaves like FCFS

### Time Quantum Selection

#### Impact of Time Quantum
```
If TQ is too SMALL:
  - Many context switches
  - High overhead
  - Process overhead dominates

If TQ is too LARGE:
  - Behaves like FCFS
  - Large waiting time
  - Poor response time

OPTIMAL TQ:
  - Related to average or median burst time
  - Typically 80-120% of average burst time
```

### Time Quantum Calculation Methods

#### Method 1: MEAN (Average)
```
Formula: TQ = SUM(Burst Times) / Number of Processes
Example: (53+43+18+16+24+73+99+27) / 8 = 353 / 8 = 44.12
Rounded: TQ = 44
```

**Characteristics:**
- Affected by outliers (very long or very short processes)
- Good general-purpose choice
- Balances between small and large processes

#### Method 2: MEDIAN
```
Formula: Middle value when burst times are sorted
Example: Sorted BT = [16, 18, 24, 27, 43, 53, 73, 99]
         Median = (27 + 43) / 2 = 35
```

**Characteristics:**
- Less affected by outliers
- Better for skewed distributions
- Represents "typical" process
- Good for systems with varied process sizes

### Example Results (from program)
```
Time Quantum Calculations:
- AVE BT (Mean): 44.12 → TQ = 44
- MEDIAN BT (Median): 35.00 → TQ = 35

Using Mean TQ (44):
AVE_TAT (Average Turnaround Time): 201.25
AVE_WT (Average Waiting Time): 157.12
```

### Execution Pattern (RR with TQ=44)
```
Time 1: P1 executes for 44 units (remaining: 53-44=9)
Time 45: P1 goes to back of queue
Time 45: P2 executes for 43 units (completes)
Time 88: P3 executes for 18 units (completes)
...
```

---

## 4. COMPARATIVE ANALYSIS

### Performance Comparison (Test Data)

| Metric | SJF | SRTF | RR (TQ=44) |
|--------|-----|------|-----------|
| **AVE_TAT** | 152.25 | **136.88** | 201.25 |
| **AVE_WT** | 108.12 | **92.75** | 157.12 |
| **Preemption** | No | Yes | Yes |
| **Predictable** | No | No | Yes |
| **Fairness** | Low | Medium | High |

### Key Observations

1. **SRTF is Best for Minimizing Wait Time**
   - 19.35 units better than SJF (136.88 vs 152.25)
   - 15.37 units better than RR (136.88 vs 201.25)

2. **SJF is Better than RR**
   - Non-preemptive nature reduces context switching
   - Still better than RR due to optimal selection

3. **RR Shows Worst Performance**
   - Due to time quantum overhead
   - Better for fairness than performance
   - Suitable when process times unknown

### When to Use Each Algorithm

| Algorithm | Best For | Worst For |
|-----------|----------|-----------|
| **SJF** | Short batch jobs, known burst times | Interactive systems, variable processes |
| **SRTF** | Minimizing waiting time, known burst times | Systems without preemption support |
| **RR** | Time-sharing, interactive systems, fairness | Minimizing average wait time |

---

## 5. IMPORTANT TERMS & DEFINITIONS

### Arrival Time (AT)
- Time when a process enters the system/ready queue
- Example: P1 arrives at time 1

### Burst Time (BT)
- Total CPU time required by a process
- Example: P1 needs 53 time units

### Completion Time (CT)
- Time when process finishes execution
- Example: P4 completes at time 20

### Turnaround Time (TAT)
- **TAT = CT - AT** (Total time in system)
- Includes waiting + execution time
- Example: P4 TAT = 20 - 4 = 16

### Waiting Time (WT)
- **WT = TAT - BT** (Time spent waiting in queue)
- Or: WT = (CT - AT) - BT
- Example: P4 WT = 16 - 16 = 0

### Average Turnaround Time (AVE_TAT)
- **AVE_TAT = SUM(TAT) / Number of Processes**
- Measures system efficiency
- Lower is better

### Average Waiting Time (AVE_WT)
- **AVE_WT = SUM(WT) / Number of Processes**
- Most important metric for users
- Lower is better

### Context Switch
- Interrupting one process to run another
- Has overhead cost
- Necessary for preemptive scheduling

### Preemption
- Ability to interrupt running process
- Required for SRTF and RR
- Allows new/better process to run

### Time Quantum (TQ)
- Fixed time slice per process in RR
- Process runs for minimum(TQ, remaining_BT)
- Critical parameter for RR performance

---

## 6. SCHEDULING DECISION EXAMPLES

### Example: Which Algorithm Performs Best?

**Given Process Data:**
```
P1: AT=1,  BT=53
P2: AT=3,  BT=43
P3: AT=8,  BT=18
P4: AT=4,  BT=16
```

**SJF Decision (Non-preemptive):**
- Time 1: Select P1 (must run to completion)
- P1 runs 1→54
- Time 54: Select P4 (shortest among remaining)
- Result: Long wait for short jobs

**SRTF Decision (Preemptive):**
- Time 1: Select P1 (BT=53)
- Time 3: P2 arrives (BT=43), PREEMPT P1
- Time 4: P4 arrives (BT=16), PREEMPT P2
- Result: Short jobs finish quickly

**RR Decision (with TQ=20):**
- Time 1: P1 runs for 20 (remaining=33)
- Time 21: P1 goes to back, P2 runs for 20
- Time 41: P2 goes to back, P3 runs for 18
- All processes get fair time slices

---

## 7. SYSTEM METRICS & CALCULATIONS

### Total Completion Time
- Last process completion time
- Example: 354 (when P7 finishes)

### CPU Utilization
- Percentage of time CPU is busy
- CPU Utilization = (Total BT / Total CT) × 100

### Throughput
- Number of processes completed per unit time
- Example: 8 processes / 354 time units = 0.0226 processes/time unit

### Response Time
- Time from submission to first execution
- Important for interactive systems

### Context Switch Frequency
- Number of times CPU switches between processes
- Affects performance in preemptive algorithms

---

## 8. ALGORITHM SELECTION FLOWCHART

```
START
  |
  ├─ Do you know burst times? 
  |  ├─ YES → Can you support preemption?
  |  |         ├─ YES → Use SRTF (optimal)
  |  |         └─ NO → Use SJF
  |  |
  |  └─ NO → Use Round Robin
  |
  ├─ Is fairness important?
  |  ├─ YES → Use Round Robin
  |  └─ NO → Use SRTF or SJF
  |
  └─ Is it interactive system?
     ├─ YES → Use Round Robin
     └─ NO → Use SRTF or SJF
```

---

## 9. REAL-WORLD APPLICATIONS

### SRTF
- High-performance computing
- Batch processing systems
- Server load balancing
- When response time is critical

### Round Robin
- Time-sharing operating systems (Unix, Linux)
- Web servers handling multiple requests
- Interactive terminal systems
- Desktop operating systems

### SJF
- Job scheduling in supercomputers
- Print queue management
- Task scheduling when burst times known
- Educational purpose

---

## 10. FORMULAS REFERENCE

```
Turnaround Time (TAT) = Completion Time (CT) - Arrival Time (AT)

Waiting Time (WT) = Turnaround Time (TAT) - Burst Time (BT)
                   = (CT - AT) - BT

Average Turnaround Time = Σ(TAT) / n

Average Waiting Time = Σ(WT) / n

Mean Burst Time = Σ(BT) / n

Median Burst Time = Middle value of sorted burst times

CPU Utilization = (Total Burst Time / Total Completion Time) × 100

Context Switch Overhead = Time for switching × Number of switches
```

---

## CONCLUSION

- **SRTF** is theoretically optimal but requires preemption and known burst times
- **SJF** is simpler and good when burst times known but no preemption available
- **Round Robin** is most practical for general-purpose systems, ensures fairness
- **Time Quantum** selection in RR is critical (typically 80-120% of mean burst time)
- **Real systems** often use hybrid approaches combining multiple algorithms

