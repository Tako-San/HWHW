/**
 * @file SqEq.cc
 * @author Tako
 * @brief file with realisations
 */

#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "SqEq.h"

bool read_coeffs(const char *prompt, double coeffs[COEFF_NUM]) {
  puts(prompt);
  int scanned = scanf("%lf %lf %lf", coeffs, coeffs + 1, coeffs + 2);
  return COEFF_NUM == scanned;
}

int solve_sqeq(const double coeffs[COEFF_NUM], double results[MAX_ROOT_NUM]) {
  if ((nullptr == coeffs) || (nullptr == results))
    return RT_NULLPTR_ERROR;

  double a = coeffs[0], b = coeffs[1], c = coeffs[2];
  if (!(isfinite(a) && isfinite(b) && isfinite(c)))
    return RT_INV_COEFF_ERROR;

  if (is_equal(a, 0))
    return (solve_linear(b, c, results));
  else if (is_equal(c, 0)) {
    if (is_equal(b, 0)) {
      results[0] = 0;
      results[1] = NAN;
      return RT_ONE_ROOT;
    } else {
      results[0] = 0;
      return (solve_linear(a, b, results + 1) + 1);
    }
  }

  else {
    double d = b * b - 4 * a * c;

    if (is_equal(d, 0)) {
      results[0] = -b / (2 * a);
      results[1] = NAN;
      return RT_ONE_ROOT;
    } else if (d < 0) {
      return RT_NO_ROOTS;
    } else if (d > 0) {
      double sqrt_d = sqrt(d);
      results[0] = (-b + sqrt_d) / (2 * a);
      results[1] = (-b - sqrt_d) / (2 * a);
      return RT_TWO_ROOTS;
    }
  }
  return RT_ERROR;
}

int solve_linear(double b, double c, double *x_ptr) {
  if (is_equal(b, 0))
    return is_equal(c, 0) ? RT_INF_ROOTS : RT_NO_ROOTS;
  else if (is_equal(c, 0)) {
    *x_ptr = 0;
    return RT_ONE_ROOT;
  } else {
    *x_ptr = -c / b;
    return RT_ONE_ROOT;
  }
}

int is_equal(double n1, double n2) { return (fabs(n1 - n2) < EPS); }

void print_res(int res_type, const double results[MAX_ROOT_NUM]) {
  printf("Answer:\n");
  switch (res_type) {
  case RT_NO_ROOTS:
    printf("No roots\n");
    break;
  case RT_ONE_ROOT:
    printf("x = %lg\n", results[0]);
    break;
  case RT_TWO_ROOTS:
    printf("x1 = %lg\nx2 = %lg\n", results[0], results[1]);
    break;
  case RT_INF_ROOTS:
    printf("Infinite number of roots\n");
    break;
  case RT_INV_COEFF_ERROR:
    printf("INVALID COEFFICIENT VALUE\n");
    break;
  case RT_NULLPTR_ERROR:
    printf("COEFF OR ROOT ARRAY IS NULLPTR\n");
    break;
  case RT_ERROR:
    printf("ERROR\n");
    break;
  default:
    printf("UNKNOWN ERROR\n");
    break;
  }
}

int ret_code(int res_type) { return (res_type >= RT_VALID) ? 0 : SQEQ_ERROR; }

static bool linear_check(int res_type, int ans_res_type, double val, double ans, const char * msg) {
  if (res_type != ans_res_type) {
    puts("FAILED: linear_check res_type");
    puts(msg);
    return false;
  }

  if (!is_equal(val, ans)) {
    puts("FAILED: linear_check result value");
    puts(msg);
    return false;
  }

  return true;
}

static bool test_linear() {
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

bool unit_testing() {
  if (!test_linear())
    return false;

  return true;
}


