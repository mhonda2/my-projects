/*Program that will reverse and print each line*/
#include <stdio.h>

#define MAXLINE 1000    /* maximum input line size */

int saveline(char line[], int maxlength);
void reverseline(char origline[], char revline[], int length);

/*Function main*/
int main(int argc, const char *argv[])
{
    int lineCount = 0;
    int len;
    char line[MAXLINE];
    char theReverse[MAXLINE];

    while ((len = saveline(line, MAXLINE)) > 0)
    {
      ++lineCount;

      reverseline(line, theReverse, len);

      printf("%s\n", theReverse);
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

/*Reverses the current line*/
void reverseline(char origline[], char theReverse[], int length)
{
  int end, count = 0;
  for ( int i = length - 1; i >= 0; --i)
  {
    if (origline[i] == '\0')
      end = origline[i];
    else
    {
      theReverse[count] = origline[i];
      ++count;
    }
  }

  theReverse[count] = '\0';
}
