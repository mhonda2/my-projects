//Converts ASCII code to character
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "openfiles.h"

#define LEN 15

int convert(const char* string);

int main(int argc, const char* argv[])
{
  const char* names[] = {"NUL","SOH","STX","ETX","EOT","ENQ",
                "ACK","BEL","BS","TAB","LF","VT","FF","CR","SO",
              "SI","DLE","DC1","DC2","DC3","DC4","NAK","SYN","ETB",
            "CAN","EM","SUB","ESC","FS","GS","RS","US"};
  const char* parity[] = {"Even","Odd"};

  FILE* fin;
  FILE* fout;
  int n;

   bool success = openfiles(argc, argv, &fin, &fout, &n);
   if (!success) { exit(1); }

   char s[LEN];
   int par;
   int code;
   n = 10;

   //Header
   printf("Original\tASCII\tDecimal\tParity\n");
   fputs("Original\tASCII\tDecimal\tParity\n", fout);

   while (fgets(s, n, fin) != NULL)
   {
     if(strlen(s) > 8) s[8] = '\0';
     else continue;

     code = convert(s);
     par = (code % 2 == 0) ? 0 : 1;

     //Binary
     printf("%s\t", s);
     fputs(s, fout);
     fputs("\t", fout);

     //Ascii character
     if(code <= 31) {
       printf("%s\t", names[code]);
       fputs(names[code], fout);
     }
     else {
       printf("%c\t", code);
       fputc(code, fout);
     }
     fputs("\t", fout);

     //Ascii number
     printf("%d\t", code);
     fputc('0', fout);  //Need to convert number to char
     fputs("\t", fout);

     //parity
     printf("%s\n", parity[par]);
     fputs(parity[par], fout);
     fputc('\n', fout);

   }
   closefiles(fin, fout);
   return 0;
}

int convert(const char* string)
{
  int decimal = 0;
  int j = 0;
  int size = strlen(string);
  while (size-- > 0) {
    int i = (string[size] - '0') * pow(2, j);
    decimal += i;
    ++j;
  }
  return decimal;
}
