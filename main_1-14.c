/*Creates a horizontal and vertical histogram of*/
/*the frequency of different characters.*/

#include <stdio.h>
#include <ctype.h>

#define IN 1  /*inside a word*/
#define OUT 0 /*outside a word*/

#define SIZE 26 /*size of array*/

void horiHist(char letters[], int appear[]);
void vertHist(char letters[], int appear[], int max);

int main(int argc, const char *argv[])
{
  char letters[SIZE] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o',
                    'p','q','r','s','t','u','v','w','x','y','z'};
  int appear[SIZE] = {0};
  long nc, nl, nw;
  int c, state = OUT;
  nc = nl = nw = 0;
  int max = 0;

  while ((c = getchar()) != EOF)
  {
    ++nc;
    if (isalpha(c))
    {
      for (int i = 0; i < SIZE; ++i)
      {
        if (tolower(c) == letters[i])
          appear[i] += 1;
        if (appear[i] > max)
          max = appear[i];
      }
    }
    if (c == '\n') { ++nl; }
    if (c == ' ' || c == '\n' || c == '\t')
    {
       state = OUT;
    }
    else if (state == OUT)
    {
      state = IN;
      ++nw;
    }
  }

  printf("%ld chars, %ld words, and %ld lines\n", nc, nw, nl);

  horiHist(letters, appear);
  vertHist(letters, appear, max);

  return 0;
}

void horiHist(char letters[], int appear[])
{
  printf("Horizontal Histogram of the frequency of characters\n\n");

  for (int x = 0; x < SIZE; ++x)
  {
    printf("%c: ", letters[x]);
    for (int y = 0; y < appear[x]; ++y)
    {
      printf("*");
      if ((y + 1) % 5 == 0) { printf("|"); }
    }
    printf("\n");
  }
}


void vertHist(char letters[], int appear[], int max)
{
  printf("\nVertical Histogram of the frequency of characters\n\n");

  for (int x = 0; x < SIZE; ++x)
  {
    printf("%2c", letters[x]);
  }
  printf("\n");

  for (int y = 0; y < SIZE; ++y)
  {
    printf("==");
  }
  printf("\n");



  for (int m = 0; m < max; ++m)
  {
    for (int i = 0; i < SIZE; ++i)
    {
      if (appear[i] > m)
        printf(" *");
      else
        printf(" -");
    }
    printf("\n");

    if ((m + 1) % 5 == 0)
    {
      for (int l = 0; l < SIZE; ++l)
      {
        printf("==");
      }
      printf("\n");
    }
  }
}
