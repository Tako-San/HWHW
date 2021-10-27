#include <stdio.h>
#include <string.h>

#include "CharBuf.hh"

CharBuf *cb_init(CharBuf *cb, size_t elem_num)
{
  if (nullptr == cb)
    return nullptr;

  cb->buf = (char *)calloc(elem_num + 1, sizeof(char));
  cb->size = elem_num;
  return cb;
}

CharBuf *cb_init(CharBuf *cb_new, const CharBuf *cb_old)
{
  if ((nullptr == cb_new) || (nullptr == cb_old))
    return nullptr;

  cb_new->size = cb_old->size;
  cb_new->buf = (char *)calloc(cb_new->size + 1, sizeof(char));
  memcpy(cb_new->buf, cb_old->buf, cb_new->size + 1);
  return cb_new;
}

CharBuf *cb_destr(CharBuf *cb)
{
  if (nullptr == cb)
    return nullptr;

  free(cb->buf);
  cb->size = 0;
  return cb;
}

StrArray *sa_init(StrArray *sa, size_t elnum)
{
  if (nullptr == sa)
    return nullptr;

  sa->lines = (String *)calloc(elnum, sizeof(String));
  sa->size = elnum;
  return sa;
}

StrArray *sa_destr(StrArray *sa)
{
  if (nullptr == sa)
    return nullptr;

  free(sa->lines);
  sa->size = 0;
  return sa;
}

void sa_print(StrArray sa, FILE *fp)
{
  for (size_t i = 0; i < sa.size; ++i)
    fprintf(fp, "%.*s\n", (int)sa.lines[i].size, sa.lines[i].buf);
}
