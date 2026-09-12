#include <stdio.h>

int n;
int trans[20][20];
int closure[20];
int count;

void eclosure(int state)
{
    int i;

    closure[count++] = state;

    for(i = 0; i < n; i++)
    {
        if(trans[state][i] == 1)
        {
            int j, found = 0;

            /* Check whether state is already present */
            for(j = 0; j < count; j++)
            {
                if(closure[j] == i)
                {
                    found = 1;
                    break;
                }
            }

            /* If not present, find its epsilon closure */
            if(!found)
            {
                eclosure(i);
            }
        }
    }
}

int main()
{
    int i, j, state;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter epsilon transition matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &trans[i][j]);
        }
    }

    printf("Enter the state: ");
    scanf("%d", &state);

    count = 0;

    eclosure(state);

    printf("E-closure(%d) = { ", state);

    for(i = 0; i < count; i++)
    {
        printf("%d ", closure[i]);
    }

    printf("}\n");

    return 0;
}
