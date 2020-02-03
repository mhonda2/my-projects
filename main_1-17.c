/*Program that will print lines that are longer than 80 characters*/
#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int saveline(char line[], int maxlength);
void copy(char keepSafe[], char curLine[]);

/*Function main*/
int main(int argc, const char *argv[])
{
    int lineCount = 0;
    int len;
    int max = 80;   /*length of lines need to be longer than this*/
    char line[MAXLINE];
    char longest[MAXLINE];

    while ((len = saveline(line, MAXLINE)) > 0)
    {
      ++lineCount;

      if (len > max)
      {
          copy(longest, line);

          printf("This line has length: %d\n", len);
          printf("%s", longest);
      }
    }

    printf("There is %d lines\n", lineCount);

    return 0;
}

/*Function to save a line to an array*/
int saveline(char currentline[], int maxlength)
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

/*copy the current longest line into an array for safe keeping*/
void copy(char keepSafe[], char curLine[])
{
  int i;
  for (i = 0; curLine[i] != '\0'; ++i)
    keepSafe[i] = curLine[i];

  keepSafe[i] = '\0';
}
