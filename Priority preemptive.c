#include <stdio.h>
#include <limits.h>

int main()
{
    int n,time=0,completed=0,highest;
    int at[20],bt[20],rt[20],pr[20],ct[20],wt[20],tat[20];

    float avg_wt=0,avg_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(int i=0;i<n;i++)
    {
        printf("\nArrival Time P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Burst Time P%d: ",i+1);
        scanf("%d",&bt[i]);

        printf("Priority P%d: ",i+1);
        scanf("%d",&pr[i]);

        rt[i]=bt[i];
    }

    while(completed<n)
    {
        highest=-1;
        int min=INT_MAX;

        for(int i=0;i<n;i++)
        {
            if(at[i]<=time && rt[i]>0 && pr[i]<min)
            {
                min=pr[i];
                highest=i;
            }
        }

        if(highest==-1)
            time++;
        else
        {
            rt[highest]--;
            time++;

            if(rt[highest]==0)
            {
                completed++;
                ct[highest]=time;
            }
        }
    }

    for(int i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        avg_wt+=wt[i];
        avg_tat+=tat[i];
    }

    printf("\nProcess\tAT\tBT\tPR\tWT\tTAT\n");

    for(int i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],pr[i],wt[i],tat[i]);

    printf("\nAverage WT=%.2f",avg_wt/n);
    printf("\nAverage TAT=%.2f\n",avg_tat/n);

    return 0;
}
