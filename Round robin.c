#include <stdio.h>

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    int at[20], bt[20], rt[20], ct[20], wt[20], tat[20];
    for (int i = 0; i < n; i++) {
        printf(" Arrival Time for Process %d: ", i + 1);
        scanf("%d", &at[i]);
        printf(" Burst Time for Process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];
    }

    printf(" Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, done = 0;
    while (done < n) {
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] > 0) {
                executed = 1;
                if (rt[i] > tq) {
                    time += tq;
                    rt[i] -= tq;
                } else {
                    time += rt[i];
                    rt[i] = 0;
                    ct[i] = time;
                    done++;
                }
            }
        }
        if (!executed) time++;
    }

    double totalWT = 0, totalTAT = 0;
    printf("\nProcess  AT  BT  WT  TAT\n");
    for (int i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
        totalWT += wt[i];
        totalTAT += tat[i];
        printf("P%d       %d   %d   %d   %d\n", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    printf("\nAverage Waiting Time = %.2f\n", totalWT / n);
    printf("Average Turnaround Time = %.2f\n", totalTAT / n);

    return 0;
}
