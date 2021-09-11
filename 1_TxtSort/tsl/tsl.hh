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

/**
 * @brief appends the src string to the dest string, overwriting the
   terminating null byte ('\0') at the end of dest, and then adds a terminating
   null byte.
 * @param[out] dst
 * @param[in] src
 * @return char*
 */
char *tsl_strcat(char *dst, const char *src);

/**
 * @brief is similar to tsl_strcat, except that it will use at most n bytes from
   src and src does not need to be null-terminated if it contains n or more
   bytes.
 * @param[out] dst
 * @param[in] src
 * @param[in] n
 * @return char*
 */
char *tsl_strncat(char *dst, const char *src, size_t n);

/**
 * @brief  reads  in at most one less than size characters from stream and
   stores them into the buffer pointed to by str. Reading stops after an EOF or
   a newline. If a newline is read, it is stored into the buffer. A terminating
   null byte ('\0') is stored after the last character in the buffer.
 * @param[out] str
 * @param[in] size
 * @param[in] stream
 * @return char*
 */
char *tsl_fgets(char *str, int size, FILE *stream);

/**
 * @brief returns a pointer to a new string which is a duplicate of the string
   str. Memory for the new string is obtained with malloc, and can be freed
   with free.
 * @param[in] str
 * @return char*
 */
char *tsl_strdup(const char *str);

#endif
