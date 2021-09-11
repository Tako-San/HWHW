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

/**
 * @brief calculates the length of the string pointed to by str, excluding the
   terminating null byte ('\0').
 * @param[in] str
 * @return  the number of bytes in the string pointed to by s.
 */
size_t tsl_strlen(const char *str);

/**
 * @brief copies the string pointed to by src, including the terminating null
   byte ('\0'), to the buffer pointed to by dest. The strings may not overlap,
   and the destination string dest must be large enough to receive the copy.
 * @param[out] dst
 * @param[in] src
 * @return char*
 */
char *tsl_strcpy(char *dst, const char *src);

/**
 * @brief  similar to tsl_strcpy, except that at most n bytes of src are copied
 * @param[out] dst 
 * @param[in] src 
 * @param[in] n 
 * @return char* 
 */
char *tsl_strncpy(char *dst, const char *src, size_t n);

#endif
