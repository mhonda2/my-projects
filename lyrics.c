#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 1000
#define MAXLINES 5000
#define ALLOCSIZE 10000

static char allocbuf[ALLOCSIZE];
static char *allocp = allocbuf;

int readlines(FILE* infile, char* lineptr);
void writelines(FILE* outfile, char* lineptr);
void qsort_(char* lineptr, int left, int right);
void swap_(char* v, int i, int j);
char* alloc(int n);
int getline_(char*, int);

int main(int argc, const char* argv[]) {
  FILE* infile;
  FILE* outfile;

  char* lineptr = alloc(MAXLEN);
  int nlines = readlines(infile, lineptr);

  qsort_(lineptr, 0, nlines - 1);

  while (nlines >= 0) {
    writelines(outfile, lineptr);
    nlines--;
  }

  return 0;
}

char* alloc(int n) {
  if (allocbuf + ALLOCSIZE - allocp >= n) {
        allocp += n;
        return allocp - n;
    } else
        return 0;
}

int readlines(FILE* infile, char* lineptr) {
  infile = fopen("spectre.txt", "r");
  char c;
  int lines = 0, x = 0, i = 0;

  if(!infile) {
    printf("Error opening file\n");
    exit(1);
  }
  else
    while((c = fgetc(infile)) != EOF) {
      if(c != '\0') {
        char* s[MAXLEN];
        *s[i++] = c;
        while((c = fgetc(infile)) != '\0' && c != EOF) {
          *s[i++] = c;
        }
        lines += 1;
        i = 0;
        lineptr[x++] = s;
      }
    }
    fclose(infile);
    return lines;
}

void writelines(FILE* outfile, char* lineptr) {
  outfile = fopen("sorted_spectre.txt", "w");
  int i = 0;

  if(!outfile) {
    printf("Error opening file\n");
    exit(1);
  }
  else {
    while(i < MAXLINES) {
      fputs(&lineptr[i], outfile);
      i++;
    }
  }
}

void swap_(char* v, int i, int j) {
  char* temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

void qsort_(char* lineptr, int left, int right) {
  int i, last;

  if (left >= right)
      return;
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++)
       if (strcmp(v[i], v[left]) < 0)
           swap(v,  ++last, i);
   swap(v, left, last);
   qsort(v, left, last−1);
   qsort(v, last+1, right);
}
