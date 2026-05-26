#include <stdio.h>

#define MAX 10

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int total[MAX], avail[MAX], work[MAX];
    int finish[MAX] = {0}, safeSeq[MAX];

    // 🔹 Input Allocation
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // 🔹 Input Max
    printf("\nEnter Max Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // 🔹 Input Total Resources
    printf("\nEnter Total Resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &total[j]);
    }

    // 🔹 Calculate Available = Total - Allocation Sum
    for (int j = 0; j < m; j++) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            sum += alloc[i][j];
        }
        avail[j] = total[j] - sum;
        work[j] = avail[j];
    }

    // 🔹 Calculate Need = Max - Allocation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // 🔹 Print Table
    printf("\nProcess\tAllocation\tMax\t\tNeed\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t", i);

        for (int j = 0; j < m; j++)
            printf("%d ", alloc[i][j]);

        printf("\t\t");

        for (int j = 0; j < m; j++)
            printf("%d ", max[i][j]);

        printf("\t\t");

        for (int j = 0; j < m; j++)
            printf("%d ", need[i][j]);

        printf("\n");
    }

    printf("\nAvailable: ");
    for (int j = 0; j < m; j++)
        printf("%d ", avail[j]);

    // 🔹 Safety Algorithm
    int count = 0;

    while (count < n) {
        int found = 0;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int possible = 1;

                for (int j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }

        if (!found) {
            printf("\n\nSystem is NOT SAFE (Deadlock possible)\n");
            return 0;
        }
    }

    printf("\n\nSystem is SAFE\nSafe Sequence: ");
    for (int i = 0; i < n; i++) {
        printf("P%d", safeSeq[i]);
        if (i != n - 1)
            printf(" -> ");
    }

    printf("\n");

    return 0;
}
