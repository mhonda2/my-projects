/*Program that will remove trailing blanks and blank lines*/
#include <stdio.h>
#include <ctype.h>

#define MAXLINE 1000    /* maximum input line size */

int readline(char line[], int maxlength);

/*Function main*/
int main(int argc, const char *argv[])
{
    int lineCount = 0;
    int len;
    char line[MAXLINE];


    while ((len = readline(line, MAXLINE)))
    {
      ++lineCount;

      if (line[0] != '\n')
      {
        for (int i = 0; line[i] != '\0'; ++i)
        {
          if ( (line[i] == ' ' || line[i] == '\t') &&
          (!( isalpha(line[i+1])) && !(isdigit(line[i+1])) && line[i+1] != '\"') )
          {
            line[i] = '\n';
            line[i + 1] = '\0';
          }
        }
        printf("%s", line);
      }

    }

    printf("There is %d lines\n", lineCount);

    return 0;
}

/*Function to save a line to an array*/
int readline(char currentline[], int maxlength)
{
    int c, i;

    for (i = 0; i < maxlength - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
      currentline[i] = c;
    }

    if (c == '\n')
    {
        currentline[i] = c;
        ++i;
    }
    currentline[i] = '\0';

    return i;
}
