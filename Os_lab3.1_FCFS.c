#include <stdio.h>
#include <stdlib.h>

struct process_struct
{
    int pid;
    int at;
    int bt;
    int st, ct, wt, rt, tat;
} ps[100];

int findmax(int a, int b)
{
    return a > b ? a : b;
}

int comparatorAT(const void *a, const void *b)
{
    int x = ((struct process_struct *)a)->at;
    int y = ((struct process_struct *)b)->at;
    if (x < y)
        return -1;
    return 1;
}

int comparatorPid(const void *a, const void *b)
{
    int x = ((struct process_struct *)a)->pid;
    int y = ((struct process_struct *)b)->pid;
    if (x < y)
        return -1;
    return 1;
}

int main()
{
    int n;
    float avg_rt = 0, avg_tat = 0, avg_wt = 0;
    float throughput, CPU_utilisation;
    int sum_rt = 0, sum_tat = 0, sum_wt = 0, total_idle = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Enter the AT of %d process: ", i);
        scanf("%d", &ps[i].at);
        ps[i].pid = i;
    }
    printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("Enter the BT of %d process: ", i);
        scanf("%d", &ps[i].bt);
    }

    qsort((void *)ps, n, sizeof(struct process_struct), comparatorAT);

    for (int i = 0; i < n; i++)
    {
        ps[i].st = (i == 0) ? ps[i].at : findmax(ps[i].at, ps[i - 1].ct);
        ps[i].ct = ps[i].st + ps[i].bt;
        ps[i].rt = ps[i].st - ps[i].at;
        ps[i].tat = ps[i].ct - ps[i].at;
        ps[i].wt = ps[i].tat - ps[i].bt;

        sum_rt += ps[i].rt;
        sum_tat += ps[i].tat;
        sum_wt += ps[i].wt;
        total_idle += (i == 0) ? 0 : (ps[i].st - ps[i - 1].ct);
    }
    int length_cycle = ps[n - 1].ct - ps[0].st;

    avg_rt = (float)sum_rt / n;
    avg_tat = (float)sum_tat / n;
    avg_wt = (float)sum_wt / n;
    throughput = (float)n / ps[n - 1].ct;
    CPU_utilisation = (float)(length_cycle - total_idle) / length_cycle;

    qsort((void *)ps, n, sizeof(struct process_struct), comparatorPid);

    printf("\nProcess No.\tAT\tCPU Burst Time\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++)
        printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].st, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    printf("\n");

    printf("\nAverage Turn Around time = %.2f ", avg_tat);
    printf("\nAverage Waiting Time = %.2f ", avg_wt);
    printf("\nAverage Response Time = %.2f ", avg_rt);
    printf("\nThroughput = %.2f", throughput);
    printf("\nCPU Utilization(Percentage) = %.2f%%", CPU_utilisation * 100);
    printf("\n");

    return 0;
}