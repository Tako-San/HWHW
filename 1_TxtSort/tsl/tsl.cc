/**
 * @file tsl.cc
 * @author Tako
 * @brief Tako's string library
 */

#include <stdio.h>

#include "tsl.hh"

int tsl_fputs(const char *str, FILE *stream) {
  for (size_t i = 0; str[i] != '\0'; ++i)
    if (!putc(str[i], stream))
      return EOF;

  return 0;
}

int tsl_puts(const char *str) {
  tsl_fputs(str, stdout);

  if (!putchar('\n'))
    return EOF;

  return 0;
}

char *tsl_strchr(char *str, int ch) {
  size_t i = 0;
  while ((str[i] != '\0') && (str[i] != ch))
    ++i;
  return (str[i] == ch) ? (str + i) : nullptr;
}

const char *tsl_const_strchr(const char *str, int ch) {
  size_t i = 0;
  while ((str[i] != '\0') && (str[i] != ch))
    ++i;
  return (str[i] == ch) ? (str + i) : nullptr;
}

size_t tsl_strlen(const char *str) {
  size_t i = 0;
  while (str[i] != '\0')
    ++i;
  return i;
}

char *tsl_strcpy(char *dst, const char *src) { return nullptr; }

char *tsl_strncpy(char *dst, const char *src, size_t n) { return nullptr; }
