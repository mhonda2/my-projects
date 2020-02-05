//Program to "fold" long input lines into two or more shorter lines
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "openfiles.h"

#define MAX 50

int main(int argc, const char *argv[])
{
  FILE* fin;
  FILE* fout;
  int n;

  bool open = openfiles(argc, argv, &fin, &fout, &n);

  if (!open) { exit(1); }

  int c;
  int counter = 0;

  while((c = fgetc(fin)) != EOF)
  {
    if (c == ' ' && counter > MAX)
    {
      fputc('\n', fout);
      counter = 0;
    }
    else if (c == '\n')
    {
      counter = 0;
      fputc(c, fout);
    }
    else
    {
      fputc(c, fout);
      ++counter;
    }
  }

  closefiles(fin, fout);

  return 0;
}
