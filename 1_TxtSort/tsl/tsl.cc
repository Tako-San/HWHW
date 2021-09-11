/**
 * @file tsl.cc
 * @author Tako
 * @brief Tako's string library
 */

#include <stdio.h>

#include "tsl.hh"

int tsl_fputs(const char *str, FILE *stream) {
  if ((nullptr == str) || (nullptr == stream))
    return EOF;

  for (size_t i = 0; str[i] != '\0'; ++i)
    if (!putc(str[i], stream))
      return EOF;

  return 0;
}

int tsl_puts(const char *str) {
  return (EOF == tsl_fputs(str, stdout)) ? EOF : putchar('\n');
}

char *tsl_strchr(char *str, int ch) {
  if (nullptr == str)
    return nullptr;

  while ((*str != '\0') && (*str != ch))
    ++str;

  return (*str == ch) ? str : nullptr;
}

const char *tsl_const_strchr(const char *str, int ch) {
  if (nullptr == str)
    return nullptr;

  while ((*str != '\0') && (*str != ch))
    ++str;

  return (*str == ch) ? str : nullptr;
}

size_t tsl_strlen(const char *str) {
  if (nullptr == str)
    return 0;

  size_t len = 0;
  while (str[len] != '\0')
    ++len;

  return len;
}

char *tsl_strcpy(char *dst, const char *src) { return nullptr; }

char *tsl_strncpy(char *dst, const char *src, size_t n) { return nullptr; }
