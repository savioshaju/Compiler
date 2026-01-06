#include <stdio.h>
#include <string.h>
#include <ctype.h>


char keywords[][10] = {"int", "float", "if", "else", "while", "for", "return"};
char line[100], word[50];
int keycount = 7;

void main()
{
    FILE *input = fopen("program.c", "r");
    FILE *output = fopen("output.txt", "w");
    int i, j;

    if (!input)
        return;

    while (fscanf(input, "%s", line) == 1)
    {
        j = 0;

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
                    int flag = 0;
                    for (int k = 0; word[k] != '\0'; k++)
                    {
                        if (!isalpha(word[k]))
                        {
                            flag = 1;
                        }
                    }
                    if (flag)
                    {
                      fprintf(output,"<number, %s>\n", word);
                    }
                    else
                    {
                        int flg = 0;
                        for (int k = 0; k < keycount; k++)
                        {
                            if (strcmp(keywords[k], word) == 0)
                            {
                                flg = 1;
                            }
                        }
                        if (flg)
                        {
                          fprintf(output,"<keyword, %s>\n", word);
                        }
                        else
                        {

                          fprintf(output,"<identifier, %s>\n", word);
                        }
                    }
                    j = 0;
                }

                if (line[i] == '(' || line[i] == ')' || line[i] == '{' || line[i] == '}' || line[i] == '[' || line[i] == ']' || line[i] == '.' || line[i] == ',' || line[i] == ';')
                {
                  fprintf(output,"<punctuator, %c>\n", line[i]);
                }
                if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/' || line[i] == '^')
                {
                  fprintf(output,"<operator, %c>\n", line[i]);
                }
            }
        }
        if (j > 0)
        {
            word[j] = '\0';
            int flag = 0;
            for (int k = 0; word[k] != '\0'; k++)
            {
                if (!isalpha(word[k]))
                {
                    flag = 1;
                }
            }
            if (flag)
            {
              fprintf(output,"<number, %s>\n", word);
            }
            else
            {
                int flg = 0;
                for (int k = 0; k < keycount; k++)
                {
                    if (strcmp(keywords[k], word) == 0)
                    {
                        flg = 1;
                    }
                }
                if (flg)
                {
                  fprintf(output,"<keyword, %s>\n", word);
                }
                else
                {

                  fprintf(output,"<identifier, %s>\n", word);
                }
            }
            j = 0;
        }
    }

    fclose(input);
}
