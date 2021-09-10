#include <stdbool.h>

#define SQEQ_ERROR 1
#define MAX_ROOT_NUM 2
#define COEFF_NUM 3

enum ResType { RT_ERROR = -1, RT_NO_ROOTS, RT_ONE_ROOT, RT_TWO_ROOTS, RT_INF_ROOTS };

/**
 * @brief Reading 3 coefficients from stdin
 * 
 * @param prompt message to user
 * @param coeffs array for coeffs, length must be >= 3
 * @return true if all OK
 * @return false on error
 */
bool read_coeffs(const char *prompt, double coeffs[COEFF_NUM]);

/**
 * @brief Print squaree equations roots
 * 
 * @param res_type defines error/number of roots
 * @param results roots
 */
void print_res(int res_type, const double results[MAX_ROOT_NUM]);

/**
 * @brief Solving square equation
 * 
 * @param coeffs array with coefficients, length must must be >= 3
 * @param results array with roots, length must must be >= 2
 * @return result type
 */
int solve_sqeq(const double coeffs[COEFF_NUM], double results[MAX_ROOT_NUM]);
