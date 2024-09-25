#include <stdio.h>
#include <stdlib.h>

struct process
{
    int pid;
    int at;
    int bt;
    int st, ct, rt, tat, wt;
} ps[100];

int findMax(int a, int b)
{
    return a > b ? a : b;
}

int comparatorPid(const void *a, const void *b)
{
    int x = ((struct process *)a)->pid;
    int y = ((struct process *)b)->pid;
    if (x < y)
        return -1;
    return 1;
}

int comparatorAT(const void *a, const void *b)
{
    int x = ((struct process *)a)->at;
    int y = ((struct process *)b)->at;
    if (x < y)
        return -1;
    return 1;
}

int main()
{
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the At of processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ps[i].at);
        ps[i].pid = i;
    }

    printf("Enter the BT of processes: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &ps[i].bt);
    }

    qsort((void *)ps, n, sizeof(struct process), comparatorAT);

    float avg_tat = 0, avg_wt = 0, avg_rt = 0;
    float throughput = 0, CPU_uti = 0;
    int totalIdle = 0;

    for (int i = 0; i < n; i++)
    {
        ps[i].st = i == 0 ? ps[i].at : findMax(ps[i - 1].ct, ps[i].at);
        ps[i].ct = ps[i].st + ps[i].bt;
        ps[i].rt = ps[i].st - ps[i].at;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;

        avg_rt += ps[i].rt;
        avg_tat += ps[i].tat;
        avg_wt += ps[i].wt;
        totalIdle += i == 0 ? ps[i].at : ps[i].st - ps[i - 1].ct;
    }

    int length_cycle = ps[n - 1].ct - ps[0].st;
    throughput = (float)n / ps[n - 1].ct;
    CPU_uti = (float)(length_cycle - totalIdle) / length_cycle;
    qsort((void *)ps, n, sizeof(struct process), comparatorPid);

    printf("\nProcess No.\tAT\tCPU Burst Time\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt,
               ps[i].st, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    }
    printf("\nAverage Waiting Time = %.2f", avg_wt / n);
    printf("\nAverage TurnAround Time = %.2f", avg_tat / n);
    printf("\nAverage Response Time = %.2f", avg_rt / n);
    printf("\nThroughput = %.2f", throughput);
    printf("\nCPU Utilisation = %.2f%%", CPU_uti * 100);
    return 0;
}