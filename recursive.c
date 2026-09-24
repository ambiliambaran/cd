#include <stdio.h>
#include <string.h>

char input[100];
int pos = 0;
int error = 0;

void E();
void EP();
void T();
void TP();
void F();

void E()
{
    T();
    EP();
}

void EP()
{
    if(input[pos] == '+')
    {
        pos++;
        T();
        EP();
    }
}

void T()
{
    F();
    TP();
}

void TP()
{
    if(input[pos] == '*')
    {
        pos++;
        F();
        TP();
    }
}

void F()
{
    if(input[pos] == 'i')
    {
        pos++;
    }
    else if(input[pos] == '(')
    {
        pos++;
        E();

        if(input[pos] == ')')
        {
            pos++;
        }
        else
        {
            error = 1;
        }
    }
    else
    {
        error = 1;
    }
}

int main()
{
    printf("Enter the input string: ");
    scanf("%s", input);

    strcat(input, "$");

    E();

    if(input[pos] == '$' && error == 0)
        printf("String Accepted\n");
    else
        printf("String Rejected\n");

    return 0;
}
