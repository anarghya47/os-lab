#include <stdio.h>
#define MAX 10

int main() {
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[MAX][MAX], request[MAX][MAX];
    int avail[MAX], work[MAX];
    int finish[MAX];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    // Request Matrix
    printf("\nEnter Request Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    // Available
    printf("\nEnter Available Resources:\n");
    for (int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
        work[j] = avail[j];
    }

    // Step 1: Initialize finish[]
    for (int i = 0; i < n; i++) {
        int zeroAlloc = 1;
        for (int j = 0; j < m; j++) {
            if (alloc[i][j] != 0) {
                zeroAlloc = 0;
                break;
            }
        }
        finish[i] = zeroAlloc; // if no allocation → already finished
    }

    // Step 2: Find processes that can finish
    int found;
    do {
        found = 0;

        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                int possible = 1;

                for (int j = 0; j < m; j++) {
                    if (request[i][j] > work[j]) {
                        possible = 0;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++)
                        work[j] += alloc[i][j];

                    finish[i] = 1;
                    found = 1;
                }
            }
        }
    } while (found);

    // Step 3: Check deadlock
    int deadlock = 0;

    printf("\nDeadlocked Processes: ");
    for (int i = 0; i < n; i++) {
        if (!finish[i]) {
            printf("P%d ", i);
            deadlock = 1;
        }
    }

    if (!deadlock)
        printf("None (No Deadlock)");

    printf("\n");

    return 0;
}
