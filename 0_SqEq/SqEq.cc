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
  assert(nullptr != coeffs);
  assert(nullptr != results);

  double a = coeffs[0], b = coeffs[1], c = coeffs[2];
  assert(isfinite(a) && isfinite(b) && isfinite(c));

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
  case RT_ERROR:
    printf("ERROR\n");
    break;
  default:
    printf("UNKNOWN ERROR\n");
    break;
  }
}