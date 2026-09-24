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

    int value[26] = {0};
    int known[26] = {0};

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter the statements:\n");

    for (i = 0; i < n; i++)
    {
        scanf(" %c = %49s", &s[i].lhs, s[i].rhs);
    }

    printf("\nAfter Constant Propagation:\n");

    for (i = 0; i < n; i++)
    {
        char *rhs = s[i].rhs;

        /* Case 1: RHS is a number */
        if (isdigit((unsigned char)rhs[0]))
        {
            value[s[i].lhs - 'a'] = atoi(rhs);
            known[s[i].lhs - 'a'] = 1;

            printf("%c = %s\n", s[i].lhs, rhs);
        }

        /* Case 2: RHS is a single variable */
        else if (strlen(rhs) == 1 && isalpha((unsigned char)rhs[0]))
        {
            int index = rhs[0] - 'a';

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
                       rhs);
            }
        }

        /* Case 3: RHS is an expression */
        else
        {
            char result[100] = "";
            int pos = 0;

            for (j = 0; rhs[j] != '\0'; j++)
            {
                if (isalpha((unsigned char)rhs[j]))
                {
                    int index = rhs[j] - 'a';

                    if (known[index])
                    {
                        char temp[20];

                        sprintf(temp, "%d", value[index]);

                        strcpy(&result[pos], temp);
                        pos += strlen(temp);
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

            /*
             * An expression such as 5+5 is not stored
             * as a constant in this simple version.
             */
            known[s[i].lhs - 'a'] = 0;
        }
    }

    return 0;
}
