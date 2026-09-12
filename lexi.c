#include <stdio.h>
#include <string.h>
#include <ctype.h>

char keywords[10][10] = {
    "int", "float", "char", "if", "else",
    "while", "for", "return", "void", "main"
};

int isKeyword(char str[])
{
    int i;

    for(i = 0; i < 10; i++)
    {
        if(strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int isOperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' ||
       ch == '/' || ch == '=' || ch == '<' ||
       ch == '>' || ch == '%')
        return 1;

    return 0;
}

int isSpecialSymbol(char ch)
{
    if(ch == '(' || ch == ')' || ch == '{' ||
       ch == '}' || ch == '[' || ch == ']' ||
       ch == ';' || ch == ',')
        return 1;

    return 0;
}

int main()
{
    char str[1000], word[100];
    int i = 0, j;

    printf("Enter the source program:\n");
    fgets(str, sizeof(str), stdin);

    while(str[i] != '\0')
    {
        /* Ignore spaces and newline */
        if(isspace(str[i]))
        {
            i++;
        }

        /* Identifier or Keyword */
        else if(isalpha(str[i]) || str[i] == '_')
        {
            j = 0;

            while(isalnum(str[i]) || str[i] == '_')
            {
                word[j++] = str[i++];
            }

            word[j] = '\0';

            if(isKeyword(word))
                printf("%s : Keyword\n", word);
            else
                printf("%s : Identifier\n", word);
        }

        /* Constant */
        else if(isdigit(str[i]))
        {
            j = 0;

            while(isdigit(str[i]))
            {
                word[j++] = str[i++];
            }

            word[j] = '\0';

            printf("%s : Constant\n", word);
        }

        /* Operator */
        else if(isOperator(str[i]))
        {
            printf("%c : Operator\n", str[i]);
            i++;
        }

        /* Special Symbol */
        else if(isSpecialSymbol(str[i]))
        {
            printf("%c : Special Symbol\n", str[i]);
            i++;
        }

        else
        {
            i++;
        }
    }

    return 0;
}
