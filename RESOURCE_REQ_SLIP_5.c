/**Q.1 Write the simulation program for demand paging and show the page scheduling  
total and number of page faults according the FIFO page replacement  
algorithm. Assume the memory of n frames. 
Reference String: 3,4,5,6,3,4,7,3,4,5,6,7,2,4,6 */

#include <stdio.h>

int main()
{
    int pages[100];
    int frames[20];

    int n, f;
    int i, j;
    int pageFaults = 0;
    int pageHits = 0;
    int pointer = 0;
    int found;

    printf("Enter number of pages in reference string: ");
    scanf("%d", &n);

    printf("Enter reference string:\n");

    for (i = 0; i < n; i++)
    {
        scanf("%d", &pages[i]);
    }

    printf("Enter number of frames: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
    {
        frames[i] = -1;
    }

    printf("\nPage\tFrames\t\tStatus\n");

    for (i = 0; i < n; i++)
    {
        found = 0;

        for (j = 0; j < f; j++)
        {
            if (frames[j] == pages[i])
            {
                found = 1;
                break;
            }
        }

        if (found == 1)
        {
            pageHits++;
        }
        else
        {
            pageFaults++;

            frames[pointer] = pages[i];

            pointer = (pointer + 1) % f;
        }

        printf("%d\t", pages[i]);

        for (j = 0; j < f; j++)
        {
            if (frames[j] == -1)
                printf("- ");
            else
                printf("%d ", frames[j]);
        }

        if (found == 1)
            printf("\tHit");
        else
            printf("\tPage Fault");

        printf("\n");
    }

    printf("\nTotal Page References = %d", n);
    printf("\nTotal Page Faults = %d", pageFaults);
    printf("\nTotal Page Hits = %d", pageHits);

    return 0;
}


/**Q2  Consider a system with ‘n’ processes and ‘m’ resource types. Accept    
number of instances for every resource type. For each process accept the allocation 
and maximum requirement matrices. Write a program to display the contents of need 
matrix and to check if the given request of a process can be granted immediately or 
not. (Use resource request algorithm) */

#include <stdio.h>

#define MAX 20

int main()
{
    int n, m;
    int total[MAX];
    int allocation[MAX][MAX];
    int max[MAX][MAX];
    int need[MAX][MAX];
    int available[MAX];
    int request[MAX];

    int i, j;
    int process;
    int valid = 1;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resource types: ");
    scanf("%d", &m);

    printf("\nEnter total instances of each resource:\n");

    for (j = 0; j < m; j++)
    {
        printf("Resource %d: ", j);
        scanf("%d", &total[j]);
    }

    printf("\nEnter Allocation Matrix:\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Maximum Requirement Matrix:\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d: ", i);

        for (j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    for (j = 0; j < m; j++)
    {
        available[j] = total[j];

        for (i = 0; i < n; i++)
        {
            available[j] -= allocation[i][j];
        }
    }

    printf("\nAllocation Matrix:\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t", i);

        for (j = 0; j < m; j++)
        {
            printf("%d ", allocation[i][j]);
        }

        printf("\n");
    }

    printf("\nMaximum Matrix:\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t", i);

        for (j = 0; j < m; j++)
        {
            printf("%d ", max[i][j]);
        }

        printf("\n");
    }

    printf("\nNeed Matrix:\n");

    for (i = 0; i < n; i++)
    {
        printf("P%d\t", i);

        for (j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    printf("\nAvailable Resources:\n");

    for (j = 0; j < m; j++)
    {
        printf("%d ", available[j]);
    }

    printf("\n");

    printf("\nEnter process number making request (0 to %d): ", n - 1);
    scanf("%d", &process);

    printf("Enter resource request for P%d:\n", process);

    for (j = 0; j < m; j++)
    {
        scanf("%d", &request[j]);
    }

    for (j = 0; j < m; j++)
    {
        if (request[j] > need[process][j])
        {
            valid = 0;
            break;
        }
    }

    if (valid == 0)
    {
        printf("\nRequest CANNOT be granted.");
        printf("\nReason: Request is greater than Need.");
        return 0;
    }

    for (j = 0; j < m; j++)
    {
        if (request[j] > available[j])
        {
            valid = 0;
            break;
        }
    }

    if (valid == 0)
    {
        printf("\nRequest CANNOT be granted immediately.");
        printf("\nReason: Required resources are not available.");
    }
    else
    {
        printf("\nRequest CAN be granted immediately.");

        for (j = 0; j < m; j++)
        {
            available[j] -= request[j];
            allocation[process][j] += request[j];
            need[process][j] -= request[j];
        }

        printf("\nResources allocated successfully.");

        printf("\nNew Available Resources:\n");

        for (j = 0; j < m; j++)
        {
            printf("%d ", available[j]);
        }

        printf("\n");
    }

    return 0;
}