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
    }

    
    return 0;
}