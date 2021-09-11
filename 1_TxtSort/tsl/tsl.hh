#ifndef TSL_H
#define TSL_H

/**
 * @brief writes the string str to stream, without terminating null byte ('\0').
 * @param[in] str
 * @param[in] stream
 * @return int
 */
int tsl_fputs(const char *str, FILE *stream);

/**
 * @brief writes the string str and a trailing newline to stdout.
 * @param[in] str
 * @return a nonnegative number on success, or EOF on error.
 */
int tsl_puts(const char *str);

/**
 * @brief returns a pointer to the first occurrence of the character c in the
   string str.
 * @param[in] str
 * @param[in] ch
 * @return char* pointer to the matched character or NULL if the character is
   not found
 */
char *tsl_strchr(char *str, int ch);

/**
 * @brief returns a pointer to the first occurrence of the character c in the
   string s.
 * @param[in] str
 * @param[in] ch
 * @return const char* pointer to the matched character or NULL if the character
   is not found
 */
const char *tsl_const_strchr(const char *str, int ch);

#endif
