#include <stdio.h>

int main() {
    int n, m, i, j, k;

    // n = number of processes
    // m = number of resources

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int allocation[n][m], max[n][m], need[n][m];
    int available[m];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Available Resources
    printf("\nEnter Available Resources:\n");
    for(i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate Need Matrix
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Display Need Matrix
    printf("\nNeed Matrix:\n");
    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    int finish[n], safeSequence[n];
    int work[m];

    // Initialize finish array
    for(i = 0; i < n; i++) {
        finish[i] = 0;
    }

    // Initialize work = available
    for(i = 0; i < m; i++) {
        work[i] = available[i];
    }

    int count = 0;

    // Banker's Algorithm
    while(count < n) {
        int found = 0;

        for(i = 0; i < n; i++) {

            // Check if process is unfinished
            if(finish[i] == 0) {

                int possible = 1;

                // Check if Need <= Work
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                // Process can execute
                if(possible) {

                    printf("\nProcess P%d is executing", i);

                    // Release allocated resources
                    for(k = 0; k < m; k++) {
                        work[k] += allocation[i][k];
                    }

                    safeSequence[count] = i;
                    count++;

                    finish[i] = 1;
                    found = 1;

                    // Display updated available resources
                    printf("\nAvailable Resources: ");
                    for(k = 0; k < m; k++) {
                        printf("%d ", work[k]);
                    }
                    printf("\n");
                }
            }
        }

        // No process could execute
        if(found == 0) {
            break;
        }
    }

    // Check Safe State
    if(count == n) {
        printf("\nSystem is in SAFE STATE\n");

        printf("Safe Sequence: ");
        for(i = 0; i < n; i++) {
            printf("P%d", safeSequence[i]);

            if(i != n - 1)
                printf(" -> ");
        }
        printf("\n");
    }
    else {
        printf("\nSystem is NOT in SAFE STATE\n");
    }

    return 0;
}
