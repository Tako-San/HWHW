#include <stdio.h>

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
    // fprintf(fp, "line.size == %zu; line.buf == %p :> ", sa.lines[i].size, sa.lines[i].buf);
    fprintf(fp, "%.*s\n", (int)sa.lines[i].size, sa.lines[i].buf);
}
