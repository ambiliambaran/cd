
#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char c)
{
    stack[++top] = c;
    stack[top + 1] = '\0';
}

void displayStack()
{
    stack[top + 1] = '\0';
    printf("%s", stack);
}

int precedence(char a, char b)
{
    if(a == '$' && b == '$')
        return '=';

    if(a == '$')
        return '<';

    if(b == '$')
        return '>';

    if(a == '(' && b == ')')
        return '=';

    if(a == '(' || b == '(')
        return '<';

    if(b == ')')
        return '>';

    if(a == ')' || a == 'i')
        return '>';

    if(b == 'i')
        return '<';

    if(a == '+' || a == '-')
    {
        if(b == '+' || b == '-')
            return '>';

        if(b == '*' || b == '/')
            return '<';
    }

    if(a == '*' || a == '/')
    {
        if(b == '+' || b == '-')
            return '>';

        if(b == '*' || b == '/')
            return '>';
    }

    return '<';
}

int main()
{
    char input[100];
    int i = 0;
    int j;
    int relation;
    char action[30];

    printf("Enter the input string: ");
    scanf("%99s", input);

    strcat(input, "$");

    push('$');

    printf("\n%-15s %-15s %s\n", "STACK", "INPUT", "ACTION");

    while(1)
    {
        /* Check for acceptance */
        if(top == 1 && stack[0] == '$' &&
           stack[1] == 'E' && input[i] == '$')
        {
            printf("%-15s %-15s ACCEPT\n", stack, input + i);
            break;
        }

        /* Find the topmost terminal in stack */
        j = top;

        while(j >= 0 && stack[j] == 'E')
            j--;

        if(j < 0)
        {
            printf("ERROR\n");
            break;
        }

        relation = precedence(stack[j], input[i]);

        /* Shift operation */
        if(relation == '<' || relation == '=')
        {
            if(input[i] == '$')
            {
                printf("ERROR\n");
                break;
            }

            push(input[i]);
            i++;

            printf("%-15s %-15s SHIFT\n", stack, input + i);
        }

        /* Reduce operation */
        else if(relation == '>')
        {
            /* E -> i */
            if(stack[top] == 'i')
            {
                top--;
                push('E');

                printf("%-15s %-15s REDUCE E->i\n",
                       stack, input + i);
            }

            /* E -> (E) */
            else if(stack[top] == ')' &&
                    top >= 2 &&
                    stack[top - 1] == 'E' &&
                    stack[top - 2] == '(')
            {
                top -= 3;
                push('E');

                printf("%-15s %-15s REDUCE E->(E)\n",
                       stack, input + i);
            }

            /* E -> E op E */
            else if(top >= 2 &&
                    stack[top] == 'E' &&
                    (stack[top - 1] == '+' ||
                     stack[top - 1] == '-' ||
                     stack[top - 1] == '*' ||
                     stack[top - 1] == '/') &&
                    stack[top - 2] == 'E')
            {
                char op = stack[top - 1];

                top -= 3;
                push('E');

                printf("%-15s %-15s REDUCE E->E%cE\n",
                       stack, input + i, op);
            }

            else
            {
                printf("ERROR\n");
                break;
            }
        }

        else
        {
            printf("ERROR\n");
            break;
        }
    }

    return 0;
}
