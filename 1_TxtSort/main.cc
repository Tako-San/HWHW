#include <stdio.h>
#include <string.h>

#include "tsl.hh"

int main() {
  tsl_puts("What's up, fellow kids?");

  const char *str = "atat";
  printf("found sym %c by address %p\n", *tsl_const_strchr(str, 't'),
         tsl_const_strchr(str, 't'));
  printf("'atat'string len is %zu\n", tsl_strlen(str));

  return 0;
}