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
  int spaceSeen = 0;

  while((c = fgetc(fin)) != EOF)
  {
    if (c != ' ')
    {
      fputc(c, fout);
    }
    else
    {
      while ((c = fgetc(fin)) == ' ')
      {
        ++spaceSeen;
      }
      int tabs = n / spacesSeen;
      int spaces = n % spacesSeen;
      while (tabs-- > 0) { fputc('\t', fout); }
      while (spaces-- > 0) { fputc(' ', fout); }
      fputc(c, fout);
    }
  }

  closefiles(fin, fout);

  return 0;
}
