#ifndef CHAR_BUF_HH
#define CHAR_BUF_HH

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
 * @param cb CharBuf object
 * @param elem_num number of elements in buffer
 * @return pointer to input CharBuf object
 */
CharBuf *cb_init(CharBuf *cb, size_t elem_num);

/**
 * @brief CharBuf destructor
 *
 * @param cb CharBuf object
 * @return pointer to input CharBuf object
 */
CharBuf *cb_destr(CharBuf *cb);

#endif // CHAR_BUF_HH
