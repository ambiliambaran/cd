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
    int n, i, j;
    int value[26];
    int known[26];

    /* Initially, no variables are known as constants */
    for (i = 0; i < 26; i++)
        known[i] = 0;

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
        char newrhs[100] = "";
        char *p = s[i].rhs;

        /* If RHS is a number */
        if (isdigit(p[0]))
        {
            value[s[i].lhs - 'a'] = atoi(p);
            known[s[i].lhs - 'a'] = 1;

            printf("%c = %s\n", s[i].lhs, p);
        }

        /* If RHS is a single variable */
        else if (strlen(p) == 1 && isalpha(p[0]))
        {
            int index = p[0] - 'a';

            if (known[index])
            {
                value[s[i].lhs - 'a'] = value[index];
                known[s[i].lhs - 'a'] = 1;

                printf("%c = %d\n",
                       s[i].lhs,
                       value[index]);
            }
            else
            {
                known[s[i].lhs - 'a'] = 0;

                printf("%c = %s\n",
                       s[i].lhs,
                       p);
            }
        }

        /* If RHS is an expression */
        else
        {
            int k = 0;
            int all_constant = 1;

            for (j = 0; p[j] != '\0'; j++)
            {
                if (isalpha(p[j]))
                {
                    int index = p[j] - 'a';

                    if (known[index])
                    {
                        char temp[20];

                        sprintf(temp, "%d", value[index]);

                        strcpy(&newrhs[k], temp);
                        k += strlen(temp);
                    }
                    else
                    {
                        newrhs[k++] = p[j];
                        all_constant = 0;
                    }
                }
                else
                {
                    newrhs[k++] = p[j];
                }
            }

            newrhs[k] = '\0';

            /*
             * If the entire expression became a constant,
             * we could evaluate it here.
             * For now, we simply display the propagated expression.
             */
            known[s[i].lhs - 'a'] = 0;

            printf("%c = %s\n",
                   s[i].lhs,
                   newrhs);
        }
    }

    return 0;
}
```
