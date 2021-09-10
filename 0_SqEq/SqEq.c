#include <stdio.h>

#include "SqEq.h"


bool read_coeffs(const char *prompt, double coeffs[COEFF_NUM]) {
  printf("%s", prompt);
  int scanned = scanf("%lf %lf %lf", coeffs, coeffs + 1, coeffs + 2);
  return COEFF_NUM == scanned;
}

int solve_sqeq(const double coeffs[COEFF_NUM], double results[MAX_ROOT_NUM]) {
  return RT_ERROR;
}

void print_res(int res_type, const double results[MAX_ROOT_NUM]) {
  printf("The end\n");
}