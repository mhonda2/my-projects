/*Program that will print the longest line*/
#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int saveline(char line[], int maxlength);
void copy(char keepSafe[], char curLine[]);

/*Function main*/
int main(int argc, const char *argv[])
{
    int lineCount = 0;
    int len;
    int max = 0;
    char line[MAXLINE];
    char longest[MAXLINE];

    while ((len = saveline(line, MAXLINE)) > 0)
    {
      ++lineCount;

      if (len > max)
      {
          max = len;
          copy(longest, line);
      }
    }
    if (max > 0)
    {
      printf("There is %d lines\n", lineCount);
      printf("Longest line has length: %d\n", max);
      printf("%s", longest);
    }

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
  for (int i = 0; curLine[i] != '\0'; ++i)
    keepSafe[i] = curLine[i];
}
