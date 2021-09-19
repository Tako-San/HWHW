#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CharBuf.hh"
#include "trace.hh"
#include "tsl.hh"

long file_size(FILE *fp);

int main(int argc, char *argv[])
{
  if (2 != argc)
  {
    tll_error("USAGE: %s input_file\n", argv[0]);
    return tll_exit_code();
  }

  char *fname = argv[1];
  FILE *fp = fopen(fname, "rb");
  if (nullptr == fp)
  {
    tll_error("Error while opening file.\n");
    return tll_exit_code();
  }

  size_t fsize = file_size(fp);
  CharBuf raw_data = {nullptr, 0};
  if (nullptr == cb_init(&raw_data, fsize))
  {
    tll_error("Error while opening file.\n");
    return tll_exit_code();
  }

  if (fread(raw_data.buf, sizeof(char), fsize, fp) < fsize)
  {
    tll_error("Error while reading file.\n");
    return tll_exit_code();
  }
  printf("%s", raw_data.buf);

  fclose(fp);
  cb_destr(&raw_data);
  return tll_exit_code();
}

long file_size(FILE *fp)
{
  if (-1 == fseek(fp, 0L, SEEK_END))
    return -1;
  long res = ftell(fp);

  rewind(fp);
  return res;
}
