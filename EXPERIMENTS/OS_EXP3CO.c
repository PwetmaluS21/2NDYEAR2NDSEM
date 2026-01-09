#include <stdio.h>

int main() {
    int p[20], bt[20], wt[20], tat[20], i, k, n, temp;
    float wtavg = 0, tatavg = 0;

    printf("Enter the number of processes-- ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        p[i] = i + 1;  
        printf("Enter Burst Time for Process %d: ", p[i]);
        scanf("%d", &bt[i]);
    }

    for(i = 0; i < n - 1; i++) {
        for(k = i + 1; k < n; k++) {
            if(bt[i] > bt[k]) {
                temp = bt[i];
                bt[i] = bt[k];
                bt[k] = temp;
                temp = p[i];
                p[i] = p[k];
                p[k] = temp;
            }
        }
    }

    wt[0] = 0;
    tat[0] = bt[0];
    tatavg = tat[0];

    for(i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        tat[i] = wt[i] + bt[i];
        wtavg += wt[i];
        tatavg += tat[i];
    }

    printf("\nPROCESS\tBURST TIME\tWAITING TIME\tTURNAROUND TIME\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time: %.2f", wtavg / n);
    printf("\nAverage Turnaround Time: %.2f\n", tatavg / n);
    return 0;
}