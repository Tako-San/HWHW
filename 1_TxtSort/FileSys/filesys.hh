#ifndef FILESYS
#define FILESYS

#include <stdio.h>

#include "CharBuf.hh"

/**
 * @brief caclulates file's size
 * 
 * @param[in] fp pointer to file
 * @return size of file in case of success, negative value otherwise.
 */
ssize_t tfl_fsize(FILE *fp);

/**
 * @brief filling buffer with data from file
 * 
 * @param[in] fname filename
 * @param[out] raw_data buffer to fill
 * @return 0 on success
 */
int file_to_buf(const char *fname, CharBuf *raw_data);

#endif // FILESYS
