#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;
int temp = 1;

void push(char ch)
{
    stack[++top] = ch;
}

char pop()
{
    return stack[top--];
}

int precedence(char ch)
{
    if(ch == '*' || ch == '/')
        return 2;

    if(ch == '+' || ch == '-')
        return 1;

    return 0;
}

int main()
{
    char infix[100];
    char postfix[100];
    char operand[100][10];
    int i, j = 0, k = 0;
    char ch;

    printf("Enter the expression: ");
    scanf("%s", infix);

    /* Convert infix to postfix */
    for(i = 0; infix[i] != '\0'; i++)
    {
        ch = infix[i];

        if(isalnum(ch))
        {
            postfix[j++] = ch;
        }
        else if(ch == '(')
        {
            push(ch);
        }
        else if(ch == ')')
        {
            while(stack[top] != '(')
                postfix[j++] = pop();

            pop();
        }
        else
        {
            while(top != -1 &&
                  precedence(stack[top]) >= precedence(ch))
            {
                postfix[j++] = pop();
            }

            push(ch);
        }
    }

    while(top != -1)
        postfix[j++] = pop();

    postfix[j] = '\0';

    /* Generate Three Address Code */
    for(i = 0; postfix[i] != '\0'; i++)
    {
        if(isalnum(postfix[i]))
        {
            char str[10];

            str[0] = postfix[i];
            str[1] = '\0';

            strcpy(operand[k++], str);
        }
        else
        {
            char op1[10], op2[10], result[10];

            strcpy(op2, operand[--k]);
            strcpy(op1, operand[--k]);

            sprintf(result, "t%d", temp++);

            printf("%s = %s %c %s\n",
                   result, op1, postfix[i], op2);

            strcpy(operand[k++], result);
        }
    }

    return 0;
}
