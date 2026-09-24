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
        int lhs = s[i].lhs - 'a';

        /* If RHS is a number */
        if (isdigit(s[i].rhs[0]))
        {
            value[lhs] = atoi(s[i].rhs);
            known[lhs] = 1;

            printf("%c = %d\n", s[i].lhs, value[lhs]);
        }

        /* If RHS is a single variable */
        else if (strlen(s[i].rhs) == 1 &&
                 isalpha(s[i].rhs[0]))
        {
            int r = s[i].rhs[0] - 'a';

            if (known[r])
            {
                value[lhs] = value[r];
                known[lhs] = 1;

                printf("%c = %d\n",
                       s[i].lhs,
                       value[lhs]);
            }
            else
            {
                known[lhs] = 0;

                printf("%c = %s\n",
                       s[i].lhs,
                       s[i].rhs);
            }
        }

        /* If RHS is an expression */
        else
        {
            char result[100];
            int pos = 0;

            for (j = 0; s[i].rhs[j] != '\0'; j++)
            {
                char ch = s[i].rhs[j];

                if (isalpha(ch))
                {
                    int r = ch - 'a';

                    if (known[r])
                    {
                        pos += sprintf(result + pos,
                                        "%d",
                                        value[r]);
                    }
                    else
                    {
                        result[pos] = ch;
                        pos++;
                    }
                }
                else
                {
                    result[pos] = ch;
                    pos++;
                }
            }

            result[pos] = '\0';

            printf("%c = %s\n",
                   s[i].lhs,
                   result);

            known[lhs] = 0;
        }
    }

    return 0;
}
