#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define NUMBER  '0'   /* signal that a number was found */
#define MAXVAL 100

size_t sp = 0;
double val[MAXVAL];

char buf[BUFSIZ];
size_t bufp = 0;

int getch_(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch_(int c) {
  if (bufp >= BUFSIZ) { fprintf(stderr, "ungetch_: Too many characters\n"); return; }
  buf[bufp++] = c;
}

int _getop(char* s) {
  int i, c, t;
  while ((s[0] = c = getch_()) == ' ' || c == '\t') { }
  s[1] = '\0';

  if (!isdigit(c) && c != '.' && c != '-') { return c; }
  if (c == '-' && !isdigit(t = getch_())) { ungetch_(t); return c; }

  i = 0;
  if (isdigit(c) || c == '-') {
    if (c == '-') {
      s[i] = c;
      s[++i] = t;
    }
    while (isdigit(s[++i] = c = getch_())) { }
  }
  s[i] = '\0';
  if (c != EOF) { ungetch_(c); }
  return NUMBER;
}

double _atof(char* s) {
  double val, power;
  int i, sign;

  for(i = 0; isspace(s[i]); i++)
      ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
      i++;
  for(val = 0.0; isdigit(s[i]); i++)
     val = 10.0 * val + (s[i] - '0');
  if (s[i] == '.')
      i++;
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }
  return sign * val / power;
}

void push(double f) {
  if (sp == MAXVAL) { fprintf(stderr, "Stack overflow -- Can't push %g\n", f);
                      return; }
  val[sp++] = f;
}

double pop(void) {
  if (sp == 0) { fprintf(stderr, "Stack underflow\n"); return 0.0; }
  return val[--sp];
}

void printTop(char* s) {
  double top = pop();
  printf("Top element is %.8g\n", top);
  push(top);
}

void duplicate(char* s) {
  double top = pop();
  double copy = top;
  push(top);
  push(copy);
}

void swapElem(char* s) {
  double first = pop();
  double second = pop();

  double temp = first;
  first = second;
  second = temp;

  push(second);
  push(first);
}

void clearStack(char* s) {
  int size = strlen(s);
  while (size >= 0) {
    pop();
    --size;
  }
}

 void rpc(void)
{
    int type, i, j;
    double op2;
    char s[BUFSIZ];

    while ((type = _getop(s)) != EOF) {
        switch (type) {
        case NUMBER:
            push(_atof(s));
            break;
        case '+':
            push(pop() + pop());
            break;
        case '*':
            push(pop() * pop());
            break;
        case '-':
            push(-(pop() - pop()));
            break;
        case '/':
            op2 = pop();
            if (op2 != 0.0)
                push(pop() / op2);
            else
                fprintf(stderr, "Can't divide by zero\n");
            break;
        case '%':
            i = pop();
            j = pop();
            if (i == 0) fprintf(stderr, "Can't divide by zero\n");
            else
              push(j % i);
            break;
        case '\n':
            printf("\t%.8g\n", pop());
            break;
        case 'p':
            printTop(s);
            break;
        case 'd':
            duplicate(s);
            break;
        case 's':
            swapElem(s);
            break;
        case 'c':
            clearStack(s);
            break;
        //case 'i':
            //op2 = pop();
            //push(pow(pop(), op2));
            //break;
        default:
            printf("error: unknown command %s\n", s);
            break;
        }
    }
}

int main(int argc, const char* argv[]) {
  rpc();

  return 0;
}
