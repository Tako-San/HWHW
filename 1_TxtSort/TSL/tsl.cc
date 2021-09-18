/**
 * @file tsl.cc
 * @author Tako
 * @brief Tako's string library
 */

#include <stdio.h>
#include <stdlib.h>

#include "tsl.hh"

int tsl_fputs(const char *str, FILE *stream)
{
  if ((nullptr == str) || (nullptr == stream))
    return EOF;

  for (size_t i = 0; str[i] != '\0'; ++i)
    if (!putc(str[i], stream))
      return EOF;

  return 0;
}

int tsl_puts(const char *str)
{
  return (EOF == tsl_fputs(str, stdout)) ? EOF : putchar('\n');
}

char *tsl_strchr(char *str, int ch)
{
  if (nullptr == str)
    return nullptr;

  while ((*str != '\0') && (*str != ch))
    ++str;

  return (*str == ch) ? str : nullptr;
}

const char *tsl_const_strchr(const char *str, int ch)
{
  if (nullptr == str)
    return nullptr;

  while ((*str != '\0') && (*str != ch))
    ++str;

  return (*str == ch) ? str : nullptr;
}

size_t tsl_strlen(const char *str)
{
  if (nullptr == str)
    return 0;

  size_t len = 0;
  while (str[len] != '\0')
    ++len;

  return len;
}

char *tsl_strcpy(char *dst, const char *src)
{
  if ((nullptr == dst) || (nullptr == src))
    return nullptr;

  char *dst_cur = dst;

  for (; '\0' != *src; ++dst_cur, ++src)
    *dst_cur = *src;

  *dst_cur = '\0';
  return dst;
}

char *tsl_strncpy(char *dst, const char *src, size_t n)
{
  if ((nullptr == dst) || (nullptr == src))
    return nullptr;

  char *dst_cur = dst;
  for (size_t i = 0; (i < n) && ('\0' != *src); ++i)
  {
    *dst_cur = *src;
    ++dst_cur, ++src;
  }

  *dst_cur = '\0';
  return dst;
}

char *tsl_strcat(char *dst, const char *src)
{
  if ((nullptr == dst) || (nullptr == src))
    return nullptr;

  char *dst_cur = dst;
  while (*dst_cur != '\0')
    ++dst_cur;

  return (nullptr == tsl_strcpy(dst_cur, src)) ? nullptr : dst;
}

char *tsl_strncat(char *dst, const char *src, size_t n)
{
  if ((nullptr == dst) || (nullptr == src))
    return nullptr;

  char *dst_cur = dst;
  for (size_t i = 0; (i < n) && (*dst_cur != '\0'); ++i, ++dst_cur)
    ;

  return (nullptr == tsl_strcpy(dst_cur, src)) ? nullptr : dst;
}

char *tsl_fgets(char *str, int size, FILE *stream)
{
  if ((nullptr == str) || (nullptr == stream) || (size < 1))
    return nullptr;

  char *str_cur = str;
  for (size_t i = 0, sz = size - 1; i < sz; ++i, ++str_cur)
  {
    char c = getc(stream);

    *str_cur = c;
    if ((EOF == c) || ('\0' == c))
      break;

    if (0 > c)
      return nullptr;

    if ('\n' == c)
    {
      ++str_cur;
      break;
    }
  }

  *str_cur = '\0';
  return str;
}

char *tsl_strdup(const char *str)
{
  if (nullptr == str)
    return nullptr;

  size_t len = tsl_strlen(str);
  char *copy_str = (char *)calloc(len + 1, sizeof(char));

  return (nullptr == copy_str) ? nullptr : tsl_strcpy(copy_str, str);
}

int tsl_test()
{
  tsl_puts("What's up, fellow kids?");

  const char *str = "atat";
  printf("found sym %c by address %p\n", *tsl_const_strchr(str, 't'), tsl_const_strchr(str, 't'));
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
