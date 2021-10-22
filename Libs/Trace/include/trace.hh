#ifndef TRACE_HH
#define TRACE_HH

enum LogLvl
{
  TLL_ERR,
  TLL_WARN,
  TLL_LOG
};

/**
 * @brief
 *
 * @param format format string
 * @param ...
 * @return upon success, return the number of characters printed
 */
int tll_verbose(const char *format, ...);

/**
 * @brief
 *
 * @param format format string
 * @param ...
 * @return upon success, return the number of characters printed
 */
int tll_warning(const char *format, ...);

/**
 * @brief
 *
 * @param format format string
 * @param ...
 * @return upon success, return the number of characters printed
 */
int tll_error(const char *format, ...);

/**
 * @brief returns exit code
 * @return 0 if no errors occured, -1 otherwise
 */
int tll_exit_code(bool leave = true);

/**
 * @brief function to set logging level
 * @param log_lvl logging level
 */
void tll_set_log_lvl(LogLvl log_lvl);

#endif // TRACE_HH