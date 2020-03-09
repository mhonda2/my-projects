#include <stdio.h>
#include <string.h>
#include <assert.h>

const char* letters = "abcdefgh";
const char* alphabet = "ijklmnop";
const char* words = "badeggs";
const char* stuff = "abde";
const char* things = "xyzs";
const char* food = "egg";
const char* drink = "soda";
char buf1[50];
char buf2[50];

void reset_buf() {
  memset(buf1, 0, 50);
  memset(buf2, 0, 50);
}

char* strcpy_(char* s, const char* t) {
  char* p = s;
  while ((*s++ = *t++) != '\0') { }
  return p;
}

char* strncpy_(char* s, const char* t, size_t n) {
  char* p = s;
  while (n-- > 0 && ((*s++ = *t++) != '\0')) { }
  while ((int)n-- > 0) { *s++ = '\0'; }
  *s++ = '\0';
  return p;
}

 int strcmp_(const char* s, const char* t) {
   while(*s != '\0' && *t != '\0' && *s == *t) {
     ++s;
     ++t;
   }
   return *s - *t;
 }

 char* strcat_(char* s, const char* t) {
   char* p = s;
   while(*s++ != '\0') { }
   --s;
   while((*s++ = *t++) != '\0') { }
   return p;
 }

 int strend_(const char* s, const char* t) {
   while(*s != '\0' && *t != '\0') {
     if(*s++ == *t) { ++t; }
   }
   return *s - *t;
 }

 size_t strspn_(const char* s, const char* t) {
   const char* p = s;
   while(*s != '\0' && strchr(t, *s) ) { ++s; }
   return s - p;
 }

 size_t strcspn_(const char* s, const char* t) {
   const char* p = s;
   while(*s != '\0' && strchr(t, *s) == NULL) { ++s; }
   return s - p;
 }

 const char* strchr_(const char* s, const char c) {
   const char* p = NULL;
   while(*s != '\0' && *s != c) { ++s; }
   if(*s != '\0') { p = s; }
   return p;
 }

 const char* strpbrk_(const char* s, const char* t) {
   const char* p = NULL;
   while(*s != '\0') {
     if(strchr(t, *s)) {
       p = s;
       return p;
     }
     ++s;
   }
   return p;
 }

 const char* strstr_(const char* s, const char* t) {
   const char* p;
   while(*s != '\0') {
     if (*s == *t) {
       p = s;
       while(*++s != '\0' && *++t != '\0' && *s == *t) { }
       if (*t == '\0') { return p; }
     }
     p = NULL;
     ++s;
   }
   return p;
 }

 size_t strlen_(const char* s) {
   const char* p = s;
   while(*s != '\0') { ++s; }
   return s - p;
 }

 char* ptr = NULL;
 char* strtok_(char* s, const char* t) {
   if(s != NULL) { ptr = s; }
   if(strlen(ptr) == 0) { return NULL; }

   size_t prefix = strcspn(ptr, t);
   size_t suffix = strspn(ptr + prefix, t);

   char* token = ptr;
   char* q = ptr + prefix;
   *q = '\0';
   ptr = q + suffix;
   return token;
 }

 void test_strspn() {
   int len = strspn_(words, stuff);
   int s = strspn_(words, things);
   printf("strspn test1: %s begins with %d letters from %s\n",words,len,stuff);
   printf("strspn test2: %s begins with %d letters from %s\n",words,s,things);
 }

 void test_strcspn() {
   int len = strcspn_(words, stuff);
   int s = strcspn_(words, things);
   printf("strcspn test1: %s begins with %d letters not from %s\n",words,len,stuff);
   printf("strcspn test2: %s begins with %d letters not from %s\n",words,s,things);
 }

 void test_strchr() {
   char c = 'd';
   char d = 'f';
   printf("strchr test1: first occurrence of %c in %s is %s\n", c, words, strchr_(words, c));
   printf("strchr test2: first occurrence of %c in %s is %s\n", d, alphabet, strchr_(alphabet, d));
 }

 void test_strpbrk() {
   const char* l = strpbrk_(words, alphabet);
   const char* s = strpbrk_(words, things);
   printf("strpbrk test1: first incident of %s in %s is %s\n",alphabet,words,l);
   printf("strpbrk test2: first incident of %s in %s is %s\n",things,words,s);
 }

 void test_strstr() {
   const char* l = strstr_(words, food);
   const char* s = strstr_(words, drink);
   printf("strstr test1: first incident of %s in %s is %s\n",food,words,l);
   printf("strstr test2: first incident of %s in %s is %s\n",drink,words,s);
 }

 void test_strlen() {
   printf("%s has length %zu\n",letters,strlen_(letters));
   printf("%s has length %zu\n",words,strlen_(words));
   printf("%s has length %zu\n",things,strlen_(things));
 }

 void test_strtok(const char* s, const char* t) {
   reset_buf();
   strcpy(buf1, s);
   strcpy(buf2, s);

   printf("Assert that strtok_ produces same output as strtok for \"%s\"\n", s);
   char* p = strtok_(buf1, t);
   char* q = strtok(buf2, t);
   printf("%12s -- %-12s\n", p, q);
   assert((p == q) || strcmp(p, q) == 0);

   while (p != NULL && q != NULL) {
     p = strtok_(NULL, t);
     q = strtok(NULL, t);
     printf("%12s -- %-12s\n", p, q);
     assert((p == q) || strcmp(p, q) == 0);
   }
   printf("\n");
 }

int main() {

  printf("regular copy: %s\n", strcpy_(buf1, letters));
  printf("n copy: %s\n", strncpy_(buf1, letters, 5));

  if(strcmp_(letters, alphabet) == 0)
    printf("strings %s and %s are the same\n", letters, alphabet);
  else
    printf("strings %s and %s are different\n", letters, alphabet);

  printf("concatenate %s on to %s to get %s\n", alphabet, letters, strcat_(buf1, alphabet));

  if(strend_(buf1, alphabet) == 0)
    printf("string %s is at the end of %s\n", alphabet, buf1);
  else
    printf("string %s is not at the end of %s\n", alphabet, buf1);

  test_strspn();
  test_strcspn();
  test_strchr();
  test_strpbrk();
  test_strstr();
  test_strlen();

  test_strtok("The lazy brown dog", " ");

  return 0;
}
