#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
struct statement
{
    char lhs;
    char rhs[20];
};

int main()
{
    struct statement s[20];
    int n, i, j;
    int value[26];
    int known[26];

    for(i = 0; i < 26; i++)
        known[i] = 0;

    printf("Enter number of statements: ");
    scanf("%d", &n);

    printf("Enter the statements:\n");

    for(i = 0; i < n; i++)
    {
        scanf(" %c = %s", &s[i].lhs, s[i].rhs);
    }

    printf("\nAfter Constant Propagation:\n");

    for(i = 0; i < n; i++)
    {
        char *p = s[i].rhs;

        /* RHS is a number */
        if(isdigit(p[0]))
        {
            value[s[i].lhs - 'a'] = atoi(p);
            known[s[i].lhs - 'a'] = 1;

            printf("%c = %s\n", s[i].lhs, p);
        }

        /* RHS is a variable */
        else if(strlen(p) == 1 && isalpha(p[0]))
        {
            int index = p[0] - 'a';

            if(known[index])
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
        else
        {
            printf("%c = %s\n",
                   s[i].lhs,
                   p);
        }
    }

    return 0;
}
