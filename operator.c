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

char precedence(char a, char b)
{
    if(a == '$' && b == '$')
        return '=';

    if(a == '$')
        return '<';

    if(b == '$')
        return '>';

    if(a == '(' && b == ')')
        return '=';

    if(a == '(')
        return '<';

    if(b == '(')
        return '<';

    if(b == ')')
        return '>';

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
    char relation;

    printf("Enter the input string: ");
    scanf("%s", input);

    strcat(input, "$");

    push('$');

    printf("\n%-15s %-15s %s\n",
           "STACK", "INPUT", "ACTION");

    while(1)
    {
        /* Accept condition */
        if(stack[top] == '$' && input[i] == '$')
        {
            printf("%-15s %-15s ACCEPT\n",
                   stack, input + i);
            break;
        }

        /* If input is operand i, shift */
        if(input[i] == 'i')
        {
            push('i');

            printf("%-15s %-15s SHIFT\n",
                   stack, input + i + 1);

            i++;
        }

        /* If input is operator */
        else
        {
            relation = precedence(stack[top], input[i]);

            if(relation == '<' || relation == '=')
            {
                push(input[i]);

                printf("%-15s %-15s SHIFT\n",
                       stack, input + i + 1);

                i++;
            }
            else if(relation == '>')
            {
                /*
                   Reduce:
                   Remove the symbols of one expression.
                   For this simple parser, replace the
                   top operand/expression by E.
                */

                if(stack[top] == 'i')
                {
                    top--;
                    push('E');

                    printf("%-15s %-15s REDUCE E->i\n",
                           stack, input + i);
                }
                else if(stack[top] == ')')
                {
                    top--;
                    if(stack[top] == 'E')
                        top--;
                    if(stack[top] == '(')
                        top--;

                    push('E');

                    printf("%-15s %-15s REDUCE E->(E)\n",
                           stack, input + i);
                }
                else
                {
                    /* Reduce E operator E */
                    if(top >= 2 &&
                       stack[top] == 'E' &&
                       (stack[top-1] == '+' ||
                        stack[top-1] == '-' ||
                        stack[top-1] == '*' ||
                        stack[top-1] == '/') &&
                       stack[top-2] == 'E')
                    {
                        char op = stack[top-1];

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
            }
            else
            {
                printf("ERROR\n");
                break;
            }
        }
    }

    return 0;
}
