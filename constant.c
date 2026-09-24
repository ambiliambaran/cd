```c
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

struct statement
{
    char lhs;
    char rhs[50];
};

int main()
{
    struct statement s[20];
    int value[26] = {0};
    int known[26] = {0};

    int n, i, j;

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter the statements:\n");

    for (i = 0; i < n; i++)
    {
        scanf(" %c = %s", &s[i].lhs, s[i].rhs);
    }

    printf("\nAfter Constant Propagation:\n");

    for (i = 0; i < n; i++)
    {
        char *rhs = s[i].rhs;
        int lhsIndex = s[i].lhs - 'a';

        /* Case 1: RHS is a constant number */
        if (isdigit((unsigned char)rhs[0]))
        {
            value[lhsIndex] = atoi(rhs);
            known[lhsIndex] = 1;

            printf("%c = %d\n", s[i].lhs, value[lhsIndex]);
        }

        /* Case 2: RHS is a single variable */
        else if (strlen(rhs) == 1 && isalpha((unsigned char)rhs[0]))
        {
            int index = rhs[0] - 'a';

            if (known[index])
            {
                value[lhsIndex] = value[index];
                known[lhsIndex] = 1;

                printf("%c = %d\n",
                       s[i].lhs,
                       value[lhsIndex]);
            }
            else
            {
                known[lhsIndex] = 0;

                printf("%c = %s\n",
                       s[i].lhs,
                       rhs);
            }
        }

        /* Case 3: RHS is an expression */
        else
        {
            char result[100];
            int pos = 0;

            for (j = 0; rhs[j] != '\0'; j++)
            {
                if (isalpha((unsigned char)rhs[j]))
                {
                    int index = rhs[j] - 'a';

                    if (known[index])
                    {
                        pos += sprintf(&result[pos],
                                       "%d",
                                       value[index]);
                    }
                    else
                    {
                        result[pos++] = rhs[j];
                    }
                }
                else
                {
                    result[pos++] = rhs[j];
                }
            }

            result[pos] = '\0';

            printf("%c = %s\n",
                   s[i].lhs,
                   result);

            known[lhsIndex] = 0;
        }
    }

    return 0;
}
```
