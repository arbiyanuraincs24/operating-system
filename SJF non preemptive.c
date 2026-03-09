#include <stdio.h>

int main()
{
    int n,i,j,time=0,smallest;
    int at[20],bt[20],ct[20],wt[20],tat[20];
    int completed=0,flag[20]={0};

    float avg_wt=0,avg_tat=0;

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++)
    {
        printf("\nArrival Time P%d: ",i+1);
        scanf("%d",&at[i]);

        printf("Burst Time P%d: ",i+1);
        scanf("%d",&bt[i]);
    }

    while(completed<n)
    {
        smallest=-1;

        for(i=0;i<n;i++)
        {
            if(at[i]<=time && flag[i]==0)
            {
                if(smallest==-1 || bt[i]<bt[smallest])
                    smallest=i;
            }
        }

        if(smallest==-1)
            time++;
        else
        {
            time+=bt[smallest];
            ct[smallest]=time;
            flag[smallest]=1;
            completed++;
        }
    }

    for(i=0;i<n;i++)
    {
        tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i];

        avg_wt+=wt[i];
        avg_tat+=tat[i];
    }

    printf("\nProcess\tAT\tBT\tWT\tTAT\n");

    for(i=0;i<n;i++)
        printf("P%d\t%d\t%d\t%d\t%d\n",i+1,at[i],bt[i],wt[i],tat[i]);

    printf("\nAverage WT=%.2f",avg_wt/n);
    printf("\nAverage TAT=%.2f\n",avg_tat/n);

    return 0;
}
