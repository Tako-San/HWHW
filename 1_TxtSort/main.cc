#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tsl.hh"

int main() {
  tsl_puts("What's up, fellow kids?");

  const char *str = "atat";
  printf("found sym %c by address %p\n", *tsl_const_strchr(str, 't'),
         tsl_const_strchr(str, 't'));
  printf("'atat'string len is %zu\n", tsl_strlen(str));

  char src[] = "Original string";
  char dst1[100] = {};
  char dst2[100] = {};

  tsl_strcpy(dst1, src);
  tsl_puts(dst1);

  tsl_strncpy(dst2, src, 8);
  tsl_puts(dst2);

  char str1[20] = "part1__";
  char str2[20] = "part2";
  tsl_strncat(str1, str2, 6);
  tsl_puts(str1);

  char str3[100] = {};
  tsl_puts("Enter a string:");
  tsl_fgets(str3, 100, stdin);
  tsl_puts(str3);

  char *str4 = tsl_strdup(str2);
  tsl_puts(str4);

  free(str4);
  return 0;
}
