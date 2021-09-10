#include <stdbool.h>

/**
 * @brief return this from main on error
 */
#define SQEQ_ERROR 1

/**
 * @brief maximal munber of roots
 */
#define MAX_ROOT_NUM 2

/**
 * @brief number of coefficients
 */
#define COEFF_NUM 3

/**
 * @brief epsilon
 */
#define EPS 1e-12

/**
 * @brief enum with result types of solve functions
 */

enum ResType { RT_ERROR = -1, RT_NO_ROOTS, RT_ONE_ROOT, RT_TWO_ROOTS, RT_INF_ROOTS };

/**
 * @brief Reading 3 coefficients from stdin
 * 
 * @param[in] prompt message to user
 * @param[out] coeffs array for coeffs, length must be >= 3
 * @return true if all OK
 * @return false on error
 */
bool read_coeffs(const char *prompt, double coeffs[COEFF_NUM]);

/**
 * @brief Print squaree equations roots
 * 
 * @param[in] res_type defines error/number of roots
 * @param[in] results roots
 */
void print_res(int res_type, const double results[MAX_ROOT_NUM]);

/**
 * @brief Solving square equation
 * 
 * @param[in] coeffs array with coefficients, length must must be >= 3
 * @param[out] results array with roots, length must must be >= 2
 * @return result type
 */
int solve_sqeq(const double coeffs[COEFF_NUM], double results[MAX_ROOT_NUM]);

/**
 * @brief Solving linear equation
 * 
 * @param[in] b coeff on x
 * @param[in] c free member
 * @param[out] x_ptr result pointer
 * @return resutl type
 */
int solve_linear(double b, double c, double *x_ptr);

/**
 * @brief Compares two double numbers
 * 
 * @param[in] n1 1st num
 * @param[in] n2 2nd num
 * @return int 
 */
int is_equal(double n1, double n2);
