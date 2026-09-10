#include <stdio.h>

int main()
{
    int n, i;
    char result, op1, op2, op;

    printf("Enter number of instructions: ");
    scanf("%d", &n);

    printf("Enter three address code:\n");

    for(i = 0; i < n; i++)
    {
        scanf(" %c=%c%c%c", &result, &op1, &op, &op2);

        printf("\nMOV AX, %c\n", op1);

        if(op == '+')
            printf("ADD AX, %c\n", op2);

        else if(op == '-')
            printf("SUB AX, %c\n", op2);

        else if(op == '*')
            printf("MUL %c\n", op2);

        else if(op == '/')
            printf("DIV %c\n", op2);

        printf("MOV %c, AX\n", result);
    }

    return 0;
}
