#include "filesys.hh"
#include "trace.hh"

ssize_t tfl_fsize(FILE *fp)
{
  if (nullptr == fp)
    return -1;

  if (-1 == fseek(fp, 0L, SEEK_END))
    return -1;
  ssize_t res = ftell(fp);

  rewind(fp);
  return res;
}

int file_to_buf(const char *fname, CharBuf *raw_data)
{
  tll_verbose("Opening file: %s\n", fname);
  FILE *fp = fopen(fname, "rb");
  if (nullptr == fp)
  {
    tll_error("Error while opening file.\n");
    return tll_exit_code();
  }

  ssize_t fsize = tfl_fsize(fp);
  if (fsize < 0)
  {
    tll_error("Can't extract file size.\n");
    return tll_exit_code();
  }

  if (nullptr == cb_init(raw_data, fsize))
  {
    tll_error("Error while opening file.\n");
    return tll_exit_code();
  }

  tll_verbose("Reading from file\n");
  if (fread(raw_data->buf, sizeof(char), fsize, fp) < fsize)
  {
    tll_error("Error while reading file.\n");
    return tll_exit_code();
  }

  tll_verbose("Closing file: %s\n", fname);
  fclose(fp);

  return tll_exit_code();
}
