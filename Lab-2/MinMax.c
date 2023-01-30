#include <stdio.h>
#include <limits.h>
int main()
{

    int nT, nM;
    printf("\nEnter number of machines and tasks : \n");
    scanf("%d%d", &nM, &nT);

    int maxMax[nM][nT];
    int tmp[nM][nT];
    int makespan = 0;
    printf("\nFill Data\n");
    for (int i = 0; i < nM; i++)
        for (int j = 0; j < nT; j++)
        {
            scanf("%d", &maxMax[i][j]);
            tmp[i][j] = maxMax[i][j];
        }

    printf("\nOriginal Data\n");

    for (int i = 0; i < nM; i++)
    {
        for (int j = 0; j < nT; j++)
            printf("%d", maxMax[i][j]);
        printf("\n");
    }

    int resultTask[nT];
    int resultMachine[nT];
    int resultTime[nT];

    int ptr = -1;

    while (ptr < nT - 1)
    {
        int time[nT], machine[nT];
        for (int j = 0; j < nT; j++)
        {
            int maximum = INT_MIN;
            int pos = -1;
            for (int i = 0; i < nM; i++)
            {
                if (maxMax[i][j] > maximum)
                {
                    maximum = maxMax[i][j];
                    pos = i;
                }
            }
            time[j] = maximum;
            machine[j] = pos;
        }

        int maximum = INT_MIN;
        int pos = -1;

        for (int j = 0; j < nT; j++)
        {
            if (time[j] > maximum)
            {
                maximum = time[j];
                pos = j;
            }
        }

        resultTask[++ptr] = pos;
        resultMachine[ptr] = machine[pos];
        resultTime[ptr] = tmp[machine[pos]][pos];
        if (maximum > makespan)
            makespan = maximum;

        for (int i = 0; i < nM; i++)
        {
            for (int j = 0; j < nT; j++)
            {
                if (j == resultTask[ptr])
                    maxMax[i][j] = INT_MIN;
                else if (i == resultMachine[ptr] && maxMax[i][j] != INT_MIN)
                    maxMax[i][j] += maximum;
                else
                    continue;
            }
        }
    }

    printf("\nScheduled Task are :\n");
    for (int i = 0; i < nT; i++)
    {
        printf("\nTask %d Runs on Machine %d with Time %d units\n", resultTask[i] + 1, resultMachine[i] + 1, resultTime[i]);
    }

    printf("\nMakespan time : %d units\n", makespan);
    return 0;
}