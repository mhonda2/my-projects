#ifndef OPENFILES_H
#define OPENFILES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool openfiles(int argc, const char* argv[],
              FILE**pfin, FILE **pfout, int *n)
{
  if (argc != 3 && argc != 4)
  {
    fprintf(stderr, "Usage: ./program file1 file2 number(optional)\n");
    return false;
  }

  *pfin = fopen(argv[1], "r");
  if (*pfin == NULL)
  {
    fprintf(stderr, "Failed to open file: %s\n", argv[1]);
    return false;
  }

  *pfout = fopen(argv[2], "w");
  if (*pfout == NULL)
  {
    fprintf(stderr, "Failed to open file: %s\n", argv[2]);
    fprintf(stderr, "Closing other open file: %s\n", argv[1]);
    fclose(*pfin);
    return false;
  }

  if(argc == 4)
  {
    *n = atoi(argv[3]);
  }
  else
    *n = 10;

  return true;
}

void closefiles(FILE* fin, FILE* fout)
{
  fclose(fin);
  fclose(fout);
}
#endif
