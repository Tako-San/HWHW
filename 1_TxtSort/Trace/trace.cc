/**
 * @file trace.cc
 * @author Tako-San
 * @brief TLL - Tako's Logging Library
 */

#include <stdarg.h>
#include <stdio.h>

#include "trace.hh"

static bool IS_FAILED = false;
static LogLvl LOG_LVL = TLL_ERR;

int tll_verbose(const char *format, ...)
{
  if (nullptr == format)
    return -1;

  if (LOG_LVL < TLL_LOG)
    return 0;

  va_list args;
  va_start(args, format);

  printf("[VERBOSE] ");
  int res = vprintf(format, args);
  va_end(args);
  return res;
}

int tll_warning(const char *format, ...)
{
  if (nullptr == format)
    return -1;

  if (LOG_LVL < TLL_WARN)
    return 0;

  va_list args;
  va_start(args, format);

  fprintf(stderr, "[WARNING] ");
  int res = vfprintf(stderr, format, args);
  va_end(args);
  return res;
}

int tll_error(const char *format, ...)
{
  IS_FAILED = true;

  if (nullptr == format)
    return -1;

  if (LOG_LVL < TLL_ERR)
    return 0;

  va_list args;
  va_start(args, format);

  fprintf(stderr, "[ERROR] ");
  int res = vfprintf(stderr, format, args);
  va_end(args);
  return res;
}

int tll_exit_code()
{
  if (!IS_FAILED)
    return 0;

  tll_error("Exiting...\n");
  return -1;
}

void tll_set_log_lvl(LogLvl log_lvl)
{
  LOG_LVL = log_lvl;
}
