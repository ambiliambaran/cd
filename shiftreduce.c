#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char c)
{
    stack[++top] = c;
}

void displayStack()
{
    int i;

    for(i = 0; i <= top; i++)
        printf("%c", stack[i]);
}

int reduce()
{
    /* E -> i */
    if(stack[top] == 'i')
    {
        stack[top] = 'E';
        return 1;
    }

    /* E -> E+E */
    if(top >= 2 &&
       stack[top] == 'E' &&
       stack[top-1] == '+' &&
       stack[top-2] == 'E')
    {
        top = top - 2;
        stack[top] = 'E';
        return 1;
    }

    /* E -> E*E */
    if(top >= 2 &&
       stack[top] == 'E' &&
       stack[top-1] == '*' &&
       stack[top-2] == 'E')
    {
        top = top - 2;
        stack[top] = 'E';
        return 1;
    }

    /* E -> (E) */
    if(top >= 2 &&
       stack[top] == ')' &&
       stack[top-1] == 'E' &&
       stack[top-2] == '(')
    {
        top = top - 2;
        stack[top] = 'E';
        return 1;
    }

    return 0;
}

int main()
{
    char input[100];
    int i = 0;

    printf("Enter the input string: ");
    scanf("%s", input);

    strcat(input, "$");

    push('$');

    printf("\n%-15s %-15s %s\n",
           "STACK", "INPUT", "ACTION");

    while(input[i] != '$')
    {
        /* SHIFT */
        push(input[i]);

        printf("%-15s %-15s SHIFT\n",
               stack, input + i + 1);

        i++;

        /* REDUCE whenever possible */
        while(reduce())
        {
            printf("%-15s %-15s REDUCE\n",
                   stack, input + i);
        }
    }

    /* Final reduction */
    while(reduce())
    {
        printf("%-15s %-15s REDUCE\n",
               stack, input + i);
    }

    if(top == 1 && stack[top] == 'E')
    {
        printf("%-15s %-15s ACCEPT\n",
               stack, input + i);
    }
    else
    {
        printf("String Rejected\n");
    }

    return 0;
}
