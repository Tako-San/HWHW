#include <stdio.h>
#include <string.h>

#include "tsl.hh"

int main() {
  tsl_puts("What's up, fellow kids?");

  const char * str = "atat";
  printf("%p %p\n", tsl_const_strchr(str, 't'), tsl_const_strchr(str, 't'));
  return 0;
}