//Program to replace spaces with tabs in a file
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
  int charSeen = 0;

  while((c = fgetc(fin)) != EOF)
  {
    if (c != ' ')
    {
      fputc(c, fout);
      ++charSeen;
    }
    else
    {
      int spaces = n - (charSeen % n);
      if (spaces < n)
      {
        fputc('\t', fout);
        charSeen += spaces;
      }
    }
  }

  closefiles(fin, fout);

  return 0;
}
