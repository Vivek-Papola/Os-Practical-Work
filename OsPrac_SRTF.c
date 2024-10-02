#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<limits.h>

struct process{
    int pid, at, bt;
    int st, ct, rt, tat, wt;
}ps[100];

int main(){
    int n;
    int rem_bt[100];
    printf("Enter the no. of processes: ");
    scanf("%d", &n);

    printf("Enter the AT: ");
    for(int i=0; i<n; i++){
        scanf("%d", &ps[i].at);
        ps[i].pid = i+1;
    }

    printf("Enter the BT: ");
    for(int i=0; i<n; i++){
        scanf("%d", &ps[i].bt);
        rem_bt[i] = ps[i].bt;
    }

    int completed = 0, curr_time = 0, total_idletime = 0;
    bool is_completed[100] = {false}, is_first_process = true;
    float avg_rt = 0, avg_tat = 0, avg_wt = 0, throughput = 0, cpu;
    int prev = 0;

    while(completed != n){
        int min_index = -1;
        int min_bt = INT_MAX;

        for(int i=0; i<n; i++){
            if(ps[i].at <= curr_time && is_completed[i] == false){
                if(rem_bt[i] < min_bt){
                    min_bt = rem_bt[i];
                    min_index = i;
                }
                if(rem_bt[i] == min_bt){
                    if(ps[i].at < ps[min_index].at){
                        min_bt = rem_bt[i];
                        min_index = i;
                    }
                }
            }
        }

        if(min_index == -1)
            curr_time++;
        else{
            if(rem_bt[min_index] == ps[min_index].bt){
                ps[min_index].st = curr_time;
                total_idletime += is_first_process == true ? 0:ps[min_index].st - prev;
                is_first_process = false;
            }
            rem_bt[min_index]--;
            curr_time++;
            prev = curr_time;
            if(rem_bt[min_index] == 0){
                ps[min_index].ct = curr_time;
                ps[min_index].rt = ps[min_index].st - ps[min_index].at;
                ps[min_index].tat = ps[min_index].ct - ps[min_index].at;
                ps[min_index].wt = ps[min_index].tat - ps[min_index].bt;
                is_completed[min_index] = true;
                completed++;

                avg_rt += ps[min_index].rt;
                avg_tat += ps[min_index].tat;
                avg_wt += ps[min_index].wt;
                
            }
        }
    }
    int length_cycle = 0;
    int max_ct = INT_MIN, min_at = INT_MAX;
    for(int i=0; i<n; i++){
        if(ps[i].ct > max_ct)
            max_ct = ps[i].ct;
        if(ps[i].at < min_at)
            min_at = ps[i].at;
    }
    length_cycle = max_ct - min_at;
    throughput = (float)n/length_cycle;
    cpu = (length_cycle-total_idletime)/length_cycle;

    printf("\nProcess No.\tAT\tCPU Burst Time\tST\tCT\tTAT\tWT\tRT\n");
    for(int i = 0; i < n; i++)
        printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid, ps[i].at, ps[i].bt, ps[i].st, ps[i].ct, ps[i].tat, ps[i].wt, ps[i].rt);
    printf("\n");
    printf("\nAverage Turn Around time= %f ", (float)avg_tat / n);
    printf("\nAverage Waiting Time= %f ", (float)avg_wt / n);
    printf("\nAverage Response Time= %f ", (float)avg_rt / n);
    printf("\nThroughput= %f", throughput);
    printf("\nCPU Utilization(Percentage)= %f", cpu * 100);

    return 0;
}