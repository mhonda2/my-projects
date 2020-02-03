/*Creates a horizontal and vertical histogram of*/
/*the number of words that have a certain number of letters.*/

#include <stdio.h>
#include <ctype.h>

#define IN 1  /*inside a word*/
#define OUT 0 /*outside a word*/

#define SIZE 18 /*size of word lengths*/

void horiHist(int word[]);
void vertHist(int word[], int max);

int main(int argc, const char *argv[])
{
  int words[SIZE] = {0};
  int count = 0;
  long nc, nl, nw, max = 0;
  int c, state = OUT;
  nc = nl = nw = 0;

  while ((c = getchar()) != EOF)
  {
    ++nc;
    if (isalpha(c) || c == '-') { ++count; }
    if (c == '\n') { ++nl; }
    if (c == ' ' || c == '\n' || c == '\t')
    {
       state = OUT;
       if (count != 0) words[count] += 1;
       if (words[count] > max) { max = words[count]; }
       count = 0;
    }
    else if (state == OUT)
    {
      state = IN;
      ++nw;
    }
  }

  printf("%ld chars, %ld words, and %ld lines\n", nc, nw, nl);

  horiHist(words);
  vertHist(words, max);

  return 0;
}

void horiHist(int word[])
{
  printf("Horizontal Histogram of word lengths\n\n");
  for (int i = 0; i < SIZE; ++i)
  {
    printf("%2d: ", i);
    for (int x = 0; x < word[i]; ++x)
    {
      printf("*");
      if ((x + 1) % 5 == 0) { printf("|"); }
    }
    printf("\n");
  }
}

void vertHist(int word[], int max)
{
  printf("\nVertical Histogram of word lengths\n\n");
  for (int y = 0; y < SIZE; ++y)
  {
    printf("%3d", y);
  }
  printf("\n ");

  for (int l = 0; l < SIZE; ++l)
  {
    printf("===");
  }
  printf("\n");


  for (int m = 0; m < max; ++m)
  {
    for (int z = 0; z < SIZE; ++z)
    {
      if (word[z] > m)
        printf("  *");
      else
        printf("  -");
    }
    printf("\n");

    if ((m + 1) % 5 == 0)
    {
      printf(" ");
      for (int l = 0; l < SIZE; ++l)
      {
        printf("===");
      }
      printf("\n");
    }
  }
}
