#include <stdbool.h>

#define SQEQ_ERROR 1
#define MAX_ROOT_NUM 2
#define COEFF_NUM 3

enum ResType { RT_ERROR = -1, RT_NO_ROOTS, RT_ONE_ROOT, RT_TWO_ROOTS, RT_INF_ROOTS };


bool read_coeffs(const char *prompt, double coeffs[COEFF_NUM]);

void print_res(int res_type, const double results[MAX_ROOT_NUM]);
int solve_sqeq(const double coeffs[COEFF_NUM], double results[MAX_ROOT_NUM]);
