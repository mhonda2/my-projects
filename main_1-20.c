//Program to replace tabs with spaces in a file
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "openfiles.h"

#define MAX 80

int main(int argc, const char *argv[])
{
  FILE* fin;
  FILE* fout;
  int n;

  bool open = openfiles(argc, argv, &fin, &fout, &n);

  if (!open) { exit(1); }

  int c;
  int charSeen = 0;
  char maxspaces[MAX];
  char spaces[MAX];
  memset(maxspaces, ' ', sizeof(maxspaces));

  while((c = fgetc(fin)) != EOF)
  {
    if (c != '\t')
    {
      fputc(c, fout);
      ++charSeen;
    }
    else
    {
      int tabs = n - (charSeen % n);
      strncpy(spaces, maxspaces, tabs);
      spaces[tabs] = '\0';
      fputs(spaces, fout);
      charSeen += strlen(spaces);
    }
  }

  closefiles(fin, fout);

  return 0;
}
