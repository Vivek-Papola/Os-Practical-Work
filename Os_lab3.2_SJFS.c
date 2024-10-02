#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<stdbool.h>

struct process{
    int pid;
    int at;
    int bt;
    int st, ct, rt, tat, wt;
}ps[100];

int main(){
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the Arrival Time: ");
    for(int i=0; i<n; i++){
        scanf("%d", &ps[i].at);
        ps[i].pid = i+1;
    }

    printf("Enter the Burst Time: ");
    for(int i=0; i<n; i++){
        scanf("%d", &ps[i].bt);
    }

    bool is_completed[100] = {false}, is_first_process = false;
    float avg_rt = 0, avg_tat = 0, avg_wt = 0, idle_time = 0, prev = 0;
    int curr_time = 0;
    int completed = 0;

    while(completed != n){
        int mini_bt = INT_MAX;
        int mini_index = -1;
        for(int i=0; i<n; i++){
            if(ps[i].at <= curr_time && is_completed[i] == false){
                if(ps[i].bt < mini_bt){
                    mini_index = i;
                    mini_bt = ps[i].bt;
                }
                if(ps[i].bt == mini_bt){
                    if(ps[i].at < ps[mini_index].at){
                        mini_index = i;
                        mini_bt = ps[i].bt;
                    }
                }
            }
        }

        if(mini_index == -1)
            curr_time++;
        else{
            ps[mini_index].st = curr_time;
            ps[mini_index].ct = curr_time + ps[mini_index].bt;
            ps[mini_index].rt = ps[mini_index].st - ps[mini_index].at;
            ps[mini_index].tat = ps[mini_index].ct - ps[mini_index].at;
            ps[mini_index].wt = ps[mini_index].tat - ps[mini_index].bt;

            avg_rt += ps[mini_index].rt;
            avg_tat += ps[mini_index].tat;
            avg_wt += ps[mini_index].wt;
            idle_time += is_first_process == true ? 0:ps[mini_index].st-prev;

            completed++;
            curr_time = ps[mini_index].ct;
            is_first_process = false;
            is_completed[mini_index] = true;
            prev = ps[mini_index].ct;
        }
    }

    // Calculate length of Process complete cycle
    int max_ct = INT_MIN;
    int min_at = INT_MAX;
    for(int i=0; i<n; i++){
        if(ps[i].ct > max_ct)
            max_ct = ps[i].ct;
        if(ps[i].at < min_at)
            min_at = ps[i].at;
    }
    int length_cycle = max_ct - min_at;
    float throughput = (float)n/length_cycle;
    float CPU_utilisation = (length_cycle - idle_time)/length_cycle;

    // OUTPUT
    printf("Process\tAT\tBT\tST\tCT\tRT\tTAT\tWT\n");
    for(int i=0; i<n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", ps[i].pid,ps[i].at,ps[i].bt,ps[i].st,ps[i].ct,ps[i].rt,ps[i].tat,ps[i].wt);
    }

    printf("Average Response Time is %.3f\n", avg_rt/n);
    printf("Average TurnAround Time is %.3f\n", avg_tat/n);
    printf("Average Waiting Time is %.3f\n", avg_wt/n);
    printf("ThroughPut is %.3f\n", throughput);
    printf("CPU Utilisation is %.3f\n", CPU_utilisation*100);
    return 0;
}