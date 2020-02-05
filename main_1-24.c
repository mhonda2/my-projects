//Program to check for excess brackets, braces, and parentheses in a file
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "openfiles.h"


int main(int argc, const char *argv[])
{
  FILE* fin;
  FILE* fout;
  int n;

  bool open = openfiles(argc, argv, &fin, &fout, &n);

  if (!open) { exit(1); }

  int c;
  int parenthSeen = 0;
  int braceSeen = 0;
  int bracketSeen = 0;
  int quoteDoubSeen = 0;
  int quoteSingSeen = 0;


  while((c = fgetc(fin)) != EOF)
  {
    if (c == '\"') /*checks for double quotes*/
    {
      if (quoteDoubSeen == 1)
        --quoteDoubSeen;
      else
        ++quoteDoubSeen;
    }

    if (c == '\'') /*checks for single quotes*/
    {
      if (quoteSingSeen == 1)
        --quoteSingSeen;
      else
        ++quoteSingSeen;
    }

    /*checks for parentheses*/
    if (c == '(' && (quoteDoubSeen != 1 && quoteSingSeen != 1))
    {
      ++parenthSeen;
    }
    if (c == ')' && (quoteDoubSeen != 1 && quoteSingSeen != 1))
    {
      if (parenthSeen == 0)
        ++parenthSeen;
      else
        --parenthSeen;
    }

    /*checks for brackets*/
    if (c == '[' && (quoteDoubSeen != 1 && quoteSingSeen != 1))
    {
      ++bracketSeen;
    }
    if (c == ']' && (quoteDoubSeen != 1 && quoteSingSeen != 1))
    {
      if (bracketSeen == 0)
        ++bracketSeen;
      else
        --bracketSeen;
    }

    /*checks for braces*/
    if (c == '{' && (quoteDoubSeen != 1 && quoteSingSeen != 1))
    {
      ++braceSeen;
    }
    if (c == '}' && (quoteDoubSeen != 1 && quoteSingSeen != 1))
    {
      if (braceSeen == 0)
        ++braceSeen;
      else
        --braceSeen;
    }

    fputc(c, fout);

  }
  fputc('\n', fout);
  if (parenthSeen > 0)
    printf("Inbalanced parentheses by: %d\n", parenthSeen);

  if (bracketSeen > 0)
    printf("Inbalanced brackets by: %d\n", bracketSeen);

  if (braceSeen > 0)
    printf("Inbalanced braces by: %d\n", braceSeen);

  if (parenthSeen == 0 && bracketSeen == 0 && braceSeen == 0)
    printf("No imbalances\n");

  closefiles(fin, fout);

  return 0;
}
