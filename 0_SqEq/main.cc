#include <stdbool.h>
#include <stdio.h>

#include "SqEq.h"
#include "SqEqConfig.h"

void print_greeting();
int print_exit_msg(const char *msg);

int main() {
  print_greeting();

  double coeffs[COEFF_NUM] = {};
  if (!read_coeffs("Input 3 coefficients:", coeffs))
    return print_exit_msg("Input finished with error\n");

  double results[MAX_ROOT_NUM] = {};
  int res_type = solve_sqeq(coeffs, results);

  print_res(res_type, results);
  return 0;
}

void print_greeting() {
  printf("Square equation solver v.%d.%d\n", SqEq_VERSION_MAJOR,
         SqEq_VERSION_MINOR);
}

int print_exit_msg(const char *msg) {
  puts(msg);
  puts("Exiting...\n");
  return SQEQ_ERROR;
}
