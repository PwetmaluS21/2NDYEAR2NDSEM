#include <stdio.h>

int main() {
    int bt[20], wt[20], tat[20], rem_bt[20], i, j, n, time, tq;
    float wtavg = 0, tatavg = 0;
    
    printf("\nEnter the number of processes -- ");
    scanf("%d", &n);
    
    for(i = 0; i < n; i++) {
        printf("Enter Burst Time for Process %d -- ", i);
        scanf("%d", &bt[i]);
        rem_bt[i] = bt[i];  // remaining burst time
    }
    
    printf("Enter Time Quantum -- ");
    scanf("%d", &tq);
    
    time = 0;
    while(1) {
        int done = 1;
        for(i = 0; i < n; i++) {
            if(rem_bt[i] > 0) {
                done = 0; // there is a pending process
                if(rem_bt[i] > tq) {
                    time += tq;
                    rem_bt[i] -= tq;
                } else {
                    time += rem_bt[i];
                    wt[i] = time - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if(done == 1) break;
    }
    
    for(i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }
    
    printf("\n\tPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for(i = 0; i < n; i++) {
        printf("\tP%d\t\t%d\t\t%d\t\t%d\n", i, bt[i], wt[i], tat[i]);
    }
    
    printf("\nAverage Waiting Time -- %f", wtavg/n);
    printf("\nAverage Turnaround Time -- %f", tatavg/n);
    
    return 0;
}