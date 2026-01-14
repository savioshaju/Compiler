#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

char keywords[][11] = {"int", "float", "if", "else", "while", "for", "return","void"};
char operators[][13] = {"=", "==", "<", "<=", ">", ">=", "+", "-", "*", "/", "^", "%", "++", "--"};
int keycount = 8, opCount = 14;
char line[100], word[50];

bool isNumber(char word[])
{
    for (int k = 0; word[k] != '\0'; k++)
    {
        if (!isdigit(word[k]))
            return false;
    }
    return true;
}

bool isKeyword(char word[])
{
    for (int k = 0; k < keycount; k++)
    {
        if (strcmp(keywords[k], word) == 0)
            return true;
    }
    return false;
}

bool isPunchtuator(char a)
{
    if (a == '(' || a == ')' || a == '{' || a == '}' || a == '[' || a == ']' || a == '.' || a == ',' || a == ';')
        return true;

    return false;
}

bool isOperator(char word[])
{
    for (int k = 0; k < opCount; k++)
    {
        if (strcmp(operators[k], word) == 0)
            return true;
    }
    return false;
}

int main()
{
    FILE *input = fopen("program.c", "r");
    FILE *output = fopen("output.txt", "w");

    int i, j;

    if (!input)
        return 0;

    while (fscanf(input, "%s", line) == 1)
    {
        j = 0;
        if (strcmp(line, "#include") == 0)
        {
            fscanf(input, "%s", line);
            continue;
        }

        for (i = 0; line[i] != '\0'; i++)
        {
            if (isalnum(line[i]) || line[i] == '_')
            {
                word[j++] = line[i];
            }
            else
            {
                if (j > 0)
                {
                    word[j] = '\0';

                    if (isNumber(word))
                        fprintf(output, "<number, %s >\n", word);
                    else if (isKeyword(word))
                        fprintf(output, "<keyword, %s >\n", word);
                    else
                        fprintf(output, "<identifier, %s >\n", word);

                    j = 0;
                    memset(word, 0, sizeof(word));
                }

                if (isPunchtuator(line[i]))
                {
                    fprintf(output, "<punctuator, %c >\n", line[i]);
                }
                else
                {
                    char op[3] = {line[i], '\0', '\0'};

                    if (line[i + 1] != '\0')
                    {
                        op[1] = line[i + 1];
                        if (isOperator(op))
                        {
                            fprintf(output, "<operator, %s >\n", op);
                            i++;
                            continue;
                        }
                    }

                    op[1] = '\0';
                    if (isOperator(op))
                        fprintf(output, "<operator, %s >\n", op);
                }
            }
        }

        if (j > 0)
        {
            word[j] = '\0';

            if (isNumber(word))
                fprintf(output, "<number, %s >\n", word);
            else if (isKeyword(word))
                fprintf(output, "<keyword, %s >\n", word);
            else
                fprintf(output, "<identifier, %s >\n", word);

            memset(word, 0, sizeof(word));
        }
    }

    fclose(input);
    fclose(output);
    return 0;
}
