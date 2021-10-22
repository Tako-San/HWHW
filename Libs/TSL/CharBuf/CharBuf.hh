#ifndef CHAR_BUF_HH
#define CHAR_BUF_HH

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Struct which keeps dynamic char array and it's size
 */
struct CharBuf
{
  char *buf;
  size_t size;
};

/**
 * @brief Alias for CharBuf struct
 */
typedef CharBuf String;

/**
 * @brief Struct to keep all strings
 */
struct StrArray
{
  String *lines;
  size_t size;
};

/**
 * @brief CharBuf constructor
 *
 * @param[out] cb CharBuf object
 * @param[in] elem_num number of elements in buffer
 * @return pointer to input CharBuf object
 */
CharBuf *cb_init(CharBuf *cb, size_t elem_num);

/**
 * @brief CharBuf destructor
 *
 * @param[out] cb CharBuf object
 * @return pointer to input CharBuf object
 */
CharBuf *cb_destr(CharBuf *cb);

/**
 * @brief StrArray constructor
 *
 * @param[out] sa StrArray object
 * @param[in] elnum number of lines
 * @return pointer to input object
 */
StrArray *sa_init(StrArray *sa, size_t elnum);

/**
 * @brief StrArray destructor
 *
 * @param[out] sa StrArray object
 * @return pointer to input object
 */
StrArray *sa_destr(StrArray *sa);

/**
 * @brief prints string array
 *
 * @param[in] sa
 */
void sa_print(StrArray sa, FILE *fp = stdout);

#endif // CHAR_BUF_HH
