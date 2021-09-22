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
  if (2 != argc)
  {
    tll_error("USAGE: %s input_file\n", argv[0]);
    return tll_exit_code();
  }

  CharBuf raw_data = {nullptr, 0};
  if (file_to_buf(argv[1], &raw_data) != 0)
    return tll_exit_code();

  tll_verbose("Splitting text to lines\n");
  StrArray parsed_data = tsl_split_lines(raw_data);

  tll_verbose("Printing original text...\n");
  sa_print(parsed_data);

  tll_verbose("Sorting text\n");
  qsort(parsed_data.lines, parsed_data.size, sizeof(CharBuf), tsl_cb_cmp);

  tll_verbose("Printing sorted text...\n");
  sa_print(parsed_data);

  tll_verbose("Calling destructors...\n");
  cb_destr(&raw_data);
  free(parsed_data.lines);
  return tll_exit_code();
}
