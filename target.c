#include <stdio.h>
#include <string.h>

int main()
{
    int n, i, j, k;
    char line[100];
    char result[20], op1[20], op2[20], op;

    printf("Enter number of three address statements: ");
    scanf("%d", &n);
    getchar();

    printf("Enter the three address code:\n");

    for(i = 0; i < n; i++)
    {
        fgets(line, sizeof(line), stdin);

        /* Remove spaces and tabs */
        k = 0;
        for(j = 0; line[j] != '\0'; j++)
        {
            if(line[j] != ' ' && line[j] != '\t' && line[j] != '\n')
            {
                line[k++] = line[j];
            }
        }
        line[k] = '\0';

        /* Read TAC: result=op1 operator op2 */
        sscanf(line, "%[^=]=%[^+*/-]%c%s",
               result, op1, &op, op2);

        printf("\nTAC: %s = %s %c %s\n", result, op1, op, op2);
        printf("8086 Assembly:\n");

        switch(op)
        {
            case '+':
                printf("MOV AX, %s\n", op1);
                printf("ADD AX, %s\n", op2);
                printf("MOV %s, AX\n", result);
                break;

            case '-':
                printf("MOV AX, %s\n", op1);
                printf("SUB AX, %s\n", op2);
                printf("MOV %s, AX\n", result);
                break;

            case '*':
                printf("MOV AX, %s\n", op1);
                printf("MUL %s\n", op2);
                printf("MOV %s, AX\n", result);
                break;

            case '/':
                printf("MOV AX, %s\n", op1);
                printf("DIV %s\n", op2);
                printf("MOV %s, AX\n", result);
                break;

            default:
                printf("Invalid operator\n");
        }
    }

    return 0;
}
