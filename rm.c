#include <stdio.h>
#include <math.h>

#define MAX 10
#define TIME_QUANTUM 10

// ---------- STRUCTURE ----------
struct Task {
    int id;
    float C, T, D;      // Execution Time, Period, Deadline
    float remaining;    // Remaining execution time
    float weight;       // Weight for proportional share
};

// ---------- RATE MONOTONIC SCHEDULING ----------
void RMS(struct Task t[], int n) {

    float U = 0, bound;

    // CPU Utilization
    for(int i = 0; i < n; i++) {
        U += (t[i].C / t[i].T);
    }

    // Liu & Layland Bound
    bound = n * (pow(2, 1.0 / n) - 1);

    printf("\n====================================");
    printf("\nRATE MONOTONIC SCHEDULING (RMS)");
    printf("\n====================================\n");

    printf("CPU Utilization = %.3f\n", U);
    printf("RMS Bound       = %.3f\n", bound);

    // Feasibility Check
    if(U <= bound)
        printf("Result: Schedulable using RMS\n");
    else
        printf("Result: Not guaranteed schedulable\n");

    // Sort tasks by Period
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {

            if(t[i].T > t[j].T) {

                struct Task temp = t[i];
                t[i] = t[j];
                t[j] = temp;
            }
        }
    }

    printf("\nPriority Order (Shortest Period First)\n");

    for(int i = 0; i < n; i++) {
        printf("Task %d -> Period = %.2f\n",
               t[i].id, t[i].T);
    }
}

// ---------- EARLIEST DEADLINE FIRST ----------
void EDF(struct Task t[], int n) {

    float U = 0;

    printf("\n====================================");
    printf("\nEARLIEST DEADLINE FIRST (EDF)");
    printf("\n====================================\n");

    // Utilization
    for(int i = 0; i < n; i++) {
        U += (t[i].C / t[i].D);
    }

    printf("CPU Utilization = %.3f\n", U);

    // Feasibility Check
    if(U <= 1)
        printf("Result: Scheduling feasible\n");
    else
        printf("Result: Scheduling NOT feasible\n");

    // Initialize remaining times
    for(int i = 0; i < n; i++) {
        t[i].remaining = t[i].C;
    }

    int completed = 0;
    int time = 0;

    printf("\nExecution Order:\n");

    while(completed < n) {

        int idx = -1;
        float minDeadline = 99999;

        // Find task with earliest deadline
        for(int i = 0; i < n; i++) {

            if(t[i].remaining > 0 &&
               t[i].D < minDeadline) {

                minDeadline = t[i].D;
                idx = i;
            }
        }

        // CPU Idle
        if(idx == -1) {
            printf("Time %d -> CPU Idle\n", time);
            time++;
            continue;
        }

        // Execute selected task
        printf("Time %d -> Task %d executing\n",
               time, t[idx].id);

        t[idx].remaining -= 1;

        // Completion check
        if(t[idx].remaining <= 0) {

            printf("Task %d completed at time %d\n",
                   t[idx].id, time + 1);

            completed++;
        }

        time++;
    }
}

// ---------- PROPORTIONAL SHARE SCHEDULING ----------
void Proportional(struct Task t[], int n) {

    float total_weight = 0;

    printf("\n====================================");
    printf("\nPROPORTIONAL SHARE SCHEDULING");
    printf("\n====================================\n");

    // Input weights
    for(int i = 0; i < n; i++) {

        printf("Enter weight for Task %d: ",
               t[i].id);

        scanf("%f", &t[i].weight);

        t[i].remaining = t[i].C;

        total_weight += t[i].weight;
    }

    int completed = 0;

    printf("\nExecution Process:\n");

    while(completed < n) {

        for(int i = 0; i < n; i++) {

            if(t[i].remaining > 0) {

                float slice =
                    (t[i].weight / total_weight)
                    * TIME_QUANTUM;

                // Avoid overshooting
                if(slice > t[i].remaining)
                    slice = t[i].remaining;

                printf("Task %d runs for %.2f units\n",
                       t[i].id, slice);

                t[i].remaining -= slice;

                printf("Remaining time of Task %d = %.2f\n",
                       t[i].id, t[i].remaining);

                // Completion check
                if(t[i].remaining <= 0) {

                    printf("Task %d completed\n",
                           t[i].id);

                    total_weight -= t[i].weight;

                    completed++;
                }
            }
        }

        printf("\n");
    }
}

// ---------- MAIN FUNCTION ----------
int main() {

    int n;

    printf("====================================\n");
    printf("REAL TIME SCHEDULING ALGORITHMS\n");
    printf("====================================\n");

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    // Validation
    if(n > MAX || n <= 0) {
        printf("Invalid number of tasks!\n");
        return 0;
    }

    struct Task t[MAX];

    // Input task details
    for(int i = 0; i < n; i++) {

        t[i].id = i + 1;

        printf("\nEnter details for Task %d\n",
               i + 1);

        printf("Execution Time (C): ");
        scanf("%f", &t[i].C);

        printf("Period (T): ");
        scanf("%f", &t[i].T);

        printf("Deadline (D): ");
        scanf("%f", &t[i].D);
    }

    // Call Scheduling Algorithms
    RMS(t, n);

    EDF(t, n);

    Proportional(t, n);

    printf("\n====================================\n");
    printf("PROGRAM COMPLETED\n");
    printf("====================================\n");

    return 0;
}
