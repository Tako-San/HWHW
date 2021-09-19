#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CharBuf.hh"
#include "trace.hh"
#include "tsl.hh"

long file_size(FILE *fp);

int main(int argc, char *argv[])
{
  tll_set_log_lvl(TLL_LOG);
  if (2 != argc)
  {
    tll_error("USAGE: %s input_file\n", argv[0]);
    return tll_exit_code();
  }

  tll_verbose("Opening file: %s\n", argv[1]);

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

  tll_verbose("Reading from file\n");
  if (fread(raw_data.buf, sizeof(char), fsize, fp) < fsize)
  {
    tll_error("Error while reading file.\n");
    return tll_exit_code();
  }
  
  tll_verbose("Closing file: %s\n", argv[1]);
  fclose(fp);

  StrArray parsed_data = tsl_split_lines(raw_data);

  for (size_t i = 0; i < parsed_data.size; ++i)
    printf("%.*s\n", parsed_data.lines[i].size, parsed_data.lines[i].buf);


  cb_destr(&raw_data);
  free(parsed_data.lines);
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
