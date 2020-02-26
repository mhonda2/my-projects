#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define MATH '1'
#define STACK '2'
#define VARIABLE '3'
#define NUMBER  '0'   /* signal that a number was found */
#define MAXVAL 100

size_t sp = 0;
double val[MAXVAL];

char buf[BUFSIZ];
size_t bufp = 0;

char variables[MAXVAL];

int getch_(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

void ungetch_(int c) {
  if (bufp >= BUFSIZ) { fprintf(stderr, "ungetch_: Too many characters\n"); return; }
  buf[bufp++] = c;
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

int _getop(char* s) {
  int i, c, t;
  while ((s[0] = c = getch_()) == ' ' || c == '\t') { }
  s[1] = '\0';


  if (isalpha(c)) {
    i = 0;
    while (isalpha(s[++i] = c = getch_())) { }
    s[i] = '\0';
    return MATH;
  }

  if (c == '@') {
    i = 0;
    while (isalpha(s[++i] = c = getch_())) { }
    s[i] = '\0';
    return STACK;
  }

  if (c == '=' || c == '?') {
    i = 0;
    s[i] = c;
    while (isalpha(s[++i] = c = getch_())) { }
    s[i] = '\0';
    return VARIABLE;
  }


  if (!isdigit(c) && c != '.' && c != '-') { return c; }
  if (c == '-' && !isdigit(t = getch_())) { ungetch_(t); return c; }

  i = 0;
  if (isdigit(c) || c == '-' || c == '.') {
    if (c == '-') {
      s[i] = c;
      s[++i] = t;
    }
    while (isdigit(s[++i] = c = getch_()) || c == '.') { if(c == '.') s[i] = c; }
  }
  s[i] = '\0';
  if (c != EOF) { ungetch_(c); }
  return NUMBER;
}

void math(char* s) {
  double op1, result = 0.0;
  if (strcmp(s, "sin") == 0) {
    result = sin(pop());
  }
  else if (strcmp(s, "cos") == 0) {
    result = cos(pop());
  }
  else if (strcmp(s, "tan") == 0) {
    result = tan(pop());
  }
  else if (strcmp(s, "asin") == 0) {
    result = asin(pop());
  }
  else if (strcmp(s, "acos") == 0) {
    result = acos(pop());
  }
  else if (strcmp(s, "atan") == 0) {
    result = atan(pop());
  }
  else if (strcmp(s, "sinh") == 0) {
    result = sinh(pop());
  }
  else if (strcmp(s, "cosh") == 0) {
    result = cosh(pop());
  }
  else if (strcmp(s, "tanh") == 0) {
    result = tanh(pop());
  }
  else if (strcmp(s, "exp") == 0) {
    result = exp(pop());
  }
  else if (strcmp(s, "log") == 0) {
    result = log(pop());
  }
  else if (strcmp(s, "pow") == 0) {
    op1 = pop();
    result = pow(pop(), op1);
  }
  else if (strcmp(s, "sqrt") == 0) {
    result = sqrt(pop());
  }
  else {
    printf("Unknown math command\n");
  }
  push(result);
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

void stack(char* s) {
  double top, copy, temp, first, second;
  ++s;

  if (strcmp(s, "print") == 0) {
    top = pop();
    printf("Top element is %.8g\n", top);
    push(top);
  }
  else if (strcmp(s, "dupl") == 0) {
    top = pop();
    copy = top;
    push(top);
    push(copy);
  }
  else if (strcmp(s, "swap") == 0) {
    first = pop();
    second = pop();

    temp = first;
    first = second;
    second = temp;

    push(second);
    push(first);
  }
  else if (strcmp(s, "clear") == 0) {
    int size = strlen(s);
    while (size >= 0) {
      pop();
      --size;
    }
  }
  else
    printf("Unkown stack command\n");
}

void variable (char* s) {
  if (*s == '=') {
    variables[*++s - 'A'] = pop();
  }
  else if (*s == '?') {
    push(variables[*++s - 'A']);
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
        case STACK:
            stack(s);
            break;
        case MATH:
            math(s);
            break;
        case VARIABLE:
            variable(s);
            break;
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
