#include <stdbool.h>
#include <stdio.h>

#include "SqEq.h"
#include "SqEqConfig.h"

void print_greeting() {
  printf("Square equation solver v.%d.%d\n", SqEq_VERSION_MAJOR,
         SqEq_VERSION_MINOR);
}

int print_exit_msg(const char *msg) {
  printf("%s", msg);
  return SQEQ_ERROR;
}

int main() {
  print_greeting();

  double coeffs[COEFF_NUM] = {};
  if (!read_coeffs("Input 3 coefficients:\n", coeffs))
    return print_exit_msg("Input finished with error\n"
                          "Exiting...\n");

  double results[MAX_ROOT_NUM] = {};
  int res_type = solve_sqeq(coeffs, results);

  print_res(res_type, results);
  return 0;
}