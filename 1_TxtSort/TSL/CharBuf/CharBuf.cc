#include "CharBuf.hh"

CharBuf *cb_init(CharBuf *cb, size_t elem_num)
{
  if (nullptr == cb)
    return nullptr;

  cb->buf = (char *)calloc(elem_num + 1, sizeof(char));
  cb->size = elem_num;
  return cb;
}

CharBuf *cb_destr(CharBuf *cb)
{
  if (nullptr == cb)
    return nullptr;

  free(cb->buf);
  cb->size = 0;
  return cb;
}

// bool cb_empty(const CharBuf cb)
// {
//   if (0 == cb.size)
//     return true;

//   return false;
// }
