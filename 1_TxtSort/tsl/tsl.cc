/**
 * @file tsl.cc
 * @author Tako
 * @brief Tako's string library
 */

#include <stdio.h>

#include "tsl.hh"

int tsl_puts(const char * string)
{
  for (size_t i = 0; string[i] != '\0'; ++i)
    if (!putchar(string[i]))
      return EOF;

  if (!putchar('\n'))
    return EOF;

  return 0;
}
