#include <stdio.h>

#define MAX 100

typedef struct {
    int pid;
    int at;
    int bt;
    int type;
    int ct;
    int tat;
    int wt;
    int start;
} Process;


void sortByArrival(Process p[], int n) {
    Process temp;
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

int main() {
    int n;
    Process p[MAX], systemQ[MAX], userQ[MAX];
    int sysCount = 0, userCount = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);


    for(int i = 0; i < n; i++) {
        printf("\nProcess %d\n", i + 1);
        printf("Enter PID: ");
        scanf("%d", &p[i].pid);
        printf("Enter Arrival Time: ");
        scanf("%d", &p[i].at);
        printf("Enter Burst Time: ");
        scanf("%d", &p[i].bt);
        printf("Enter Type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);
    }


    for(int i = 0; i < n; i++) {
        if(p[i].type == 0)
            systemQ[sysCount++] = p[i];
        else
            userQ[userCount++] = p[i];
    }


    sortByArrival(systemQ, sysCount);
    sortByArrival(userQ, userCount);

    int time = 0;


    for(int i = 0; i < sysCount; i++) {
        if(time < systemQ[i].at)
            time = systemQ[i].at;

        systemQ[i].start = time;
        time += systemQ[i].bt;

        systemQ[i].ct = time;
        systemQ[i].tat = systemQ[i].ct - systemQ[i].at;
        systemQ[i].wt = systemQ[i].tat - systemQ[i].bt;
    }


    for(int i = 0; i < userCount; i++) {
        if(time < userQ[i].at)
            time = userQ[i].at;

        userQ[i].start = time;
        time += userQ[i].bt;

        userQ[i].ct = time;
        userQ[i].tat = userQ[i].ct - userQ[i].at;
        userQ[i].wt = userQ[i].tat - userQ[i].bt;
    }


    printf("\nPID\tAT\tBT\tTYPE\tCT\tTAT\tWT\n");


    for(int i = 0; i < sysCount; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               systemQ[i].pid,
               systemQ[i].at,
               systemQ[i].bt,
               systemQ[i].type,
               systemQ[i].ct,
               systemQ[i].tat,
               systemQ[i].wt);
    }


    for(int i = 0; i < userCount; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               userQ[i].pid,
               userQ[i].at,
               userQ[i].bt,
               userQ[i].type,
               userQ[i].ct,
               userQ[i].tat,
               userQ[i].wt);
    }

    return 0;
}
