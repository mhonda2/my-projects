//Converts ASCII code to character
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int convert(char* string[]);

int main(int argc, const char* argv[])
{
  const char* names[] = {"NUL","SOH","STX","ETX","EOT","ENQ",
                "ACK","BEL","BS","TAB","LF","VT","FF","CR","SO",
              "SI","DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB",
            "CAN","EM","SUB","ESC","FS","GS","RS","US"};
  const char* parity[] = {"Even","Odd"};
  //
  // FILE* fin;
  // FILE* fout;
  // int n;

  char* asc = "01000001";
  printf("%s is %d\n", convert(asc));
  // bool success = openfile(argc, argv, &fin, &fout, &n);
  // if (!success) { exit(1); }
  //
  // char* s[n];
  // int par;
  // int code;
  //
  // while (fgets(s[], n, fin) != EOF)
  // {
  //   code = convert(s, n);
  //
  //   /*printf("Original\tASCII\tDecimal\t");*/
  //   /*printf("%s\t%c\t%\t%d\t%s",);*/
  //
  //   printf("%d\n", code);
  // }
return 0;
}

int convert(char* string[])
{
  int decimal = 0;
  int j = 0;
  int size = strlen(string) - 2;  // skipping extended ascii
  while (size-- >= 0) {
    int i = (string[size] - '0') * pow(2, size);
    decimal += i;
  }
  return decimal;
}
