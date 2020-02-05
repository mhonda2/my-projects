//Program to remove comments from a file
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
  int slashSeen = 0;
  int starSeen = 0;
  int starSlashSeen = 0;
  int quoteSeen = 0;


  while((c = fgetc(fin)) != EOF)
  {
    if (c == '\"' && quoteSeen != 1)
    {
      ++quoteSeen;
    }
    if (c == '/' && slashSeen <= 2)
    {
      ++slashSeen;
    }
    if (c == '*' && slashSeen > 0 && starSeen == 0)
    {
      ++starSlashSeen;
      --slashSeen;
    }
    if (c == '*' && starSlashSeen == 1)
    {
      ++starSeen;
    }

    if (c == '/' && starSeen >= 1 && starSlashSeen == 1)
    {
      --starSeen;
      --starSlashSeen;
      --slashSeen;
      c = ' ';
      if (charSeen == 0)
        fputc('\n', fout);
    }

    if (slashSeen == 2 && c == '\n' && quoteSeen == 0)
    {
      slashSeen = 0;
    }

    if (c == '\"' && quoteSeen == 1)
    {
      --quoteSeen;
    }

    if ((slashSeen == 0 && starSlashSeen == 0) || quoteSeen == 1)
    {
      if (charSeen > 0)
        fputc(c, fout);
      ++charSeen;
    }

  }
  fputc('\n', fout);

  closefiles(fin, fout);

  return 0;
}
