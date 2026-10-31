
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

            for(j = 0; j < count; j++)
            {
                if(closure[j] == i)
                {
                    found = 1;
                    break;
                }
            }

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

    if(n < 1 || n > 20)
    {
        printf("Invalid number of states!\n");
        return 0;
    }

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

    if(state < 0 || state >= n)
    {
        printf("Invalid state!\n");
        return 0;
    }

    count = 0;
    eclosure(state);

    printf("E-closure(q%d) = { ", state);

    for(i = 0; i < count; i++)
    {
        printf("q%d", closure[i]);

        if(i < count - 1)
        {
            printf(", ");
        }
    }

    printf(" }\n");

    return 0;
}
