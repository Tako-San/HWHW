#include <math.h>
#include <stdio.h>

#include "SqEq.hh"

static bool linear_check(int res_type, int ans_res_type, double val, double ans, const char *msg)
{
  if (res_type != ans_res_type)
  {
    puts("FAILED: linear_check res_type");
    puts(msg);
    return false;
  }

  if (!is_equal(val, ans))
  {
    puts("FAILED: linear_check result value");
    puts(msg);
    return false;
  }

  return true;
}

static bool test_linear()
{
  int res_type = RT_ERROR;
  double x = NAN;

  // test 1
  res_type = solve_linear(1, 2, &x);
  if (!linear_check(res_type, RT_ONE_ROOT, x, -2, "x + 2 = 0 |=> x = -2"))
    return false;

  // test 2
  res_type = solve_linear(5, 0, &x);
  if (!linear_check(res_type, RT_ONE_ROOT, x, 0, "5x + 0 = 0 |=> x = 0"))
    return false;

  // test 3
  res_type = solve_linear(0, 1, &x);
  if (!linear_check(res_type, RT_NO_ROOTS, x, 0, "0x + 1 = 0 |=> NO ROOTS"))
    return false;

  // test 4
  res_type = solve_linear(0, 0, &x);
  if (!linear_check(res_type, RT_INF_ROOTS, x, 0, "0x + 0 = 0 |=> INF ROOTS"))
    return false;

  return true;
}

// TODO(Tako): Finish this stuff
static bool test_square()
{
  return true;
}

bool unit_testing()
{
  if (!test_linear())
    return false;

  if (!test_square())
    return false;

  return true;
}
