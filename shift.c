#include <stdio.h>
#include <stdlib.h>

char input[50];
int pos = 0;

void E();
void Eprime();
void T();
void Tprime();
void F();

void E()
{
    T();
    Eprime();
}

void Eprime()
{
    if (input[pos] == '+')
    {
        pos++;
        T();
        Eprime();
    }
}

void T()
{
    F();
    Tprime();
}

void Tprime()
{
    if (input[pos] == '*')
    {
        pos++;
        F();
        Tprime();
    }
}

void F()
{
    if (input[pos] == 'i')
    {
        pos++;
    }
    else if (input[pos] == '(')
    {
        pos++;
        E();

        if (input[pos] == ')')
            pos++;
        else
        {
            printf("Error: Missing )\n");
            exit(0);
        }
    }
    else
    {
        printf("Error: Invalid symbol\n");
        exit(0);
    }
}

int main()
{
    printf("Enter the input string: ");
    scanf("%s", input);

    E();

    if (input[pos] == '$')
        printf("String Accepted\n");
    else
        printf("String Rejected\n");

    return 0;
}
