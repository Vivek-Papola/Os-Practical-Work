/*        Binary search       */
#include <stdio.h>
int main()
{
    int i, first, last, middle, n, key, arr[100];
    printf("Enter the number of elements: ");
    scanf("%d", &n);
    printf("Enter %d numbers: ", n);
    for (i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    printf("Enter a key to search: ");
    scanf("%d", &key);
    first = 0;
    last = n - 1;
    middle = (first + last) / 2;
    /*     Searching process      */
    while (first <= last)
    {
        if (arr[middle] < key)
        {
            first = middle + 1;
        }
        else if (arr[middle] == key)
        {
            printf("%d found at location %d\n", key, middle + 1);
            break;
        }
        else
            last = middle - 1;
        middle = (first + last) / 2;
    }
    if (first > last)
        printf("Not found\n");
    return 0;
}
