#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CharBuf.hh"
#include "filesys.hh"
#include "trace.hh"
#include "tsl.hh"

int main(int argc, char *argv[])
{
  tll_set_log_lvl(TLL_LOG);
  if ((argc != 3) && (argc != 2))
  {
    tll_error("USAGE: %s input_file [output_file]\n", argv[0]);
    return tll_exit_code();
  }

  FILE *out_fp = (argc == 2) ? stdout : fopen(argv[2], "wb");
  if (nullptr == out_fp)
  {
    tll_error("Error opening output file\n");
    return tll_exit_code();
  }

  CharBuf raw_data = {nullptr, 0};
  if (file_to_buf(argv[1], &raw_data) != 0)
    return tll_exit_code();

  tll_verbose("Splitting text to lines\n");
  StrArray parsed_data = tsl_split_lines(raw_data);
  if (0 == parsed_data.size)
  {
    tll_error("Error while splitting file\n");
    return tll_exit_code();
  }

  tll_verbose("Printing original text...\n");
  sa_print(parsed_data, out_fp);

  tll_verbose("Sorting text\n");
  qsort(parsed_data.lines, parsed_data.size, sizeof(CharBuf), tsl_cb_cmp);

  tll_verbose("Printing sorted text...\n");
  sa_print(parsed_data, out_fp);

  tll_verbose("Sorting text backwards\n");
  qsort(parsed_data.lines, parsed_data.size, sizeof(CharBuf), tsl_cb_back_cmp);

  tll_verbose("Printing backwards sorted text...\n");
  sa_print(parsed_data, out_fp);

  tll_verbose("Calling destructors...\n");
  sa_destr(&parsed_data);
  cb_destr(&raw_data);

  tll_verbose("Executing finished.\n");
  return tll_exit_code();
}
