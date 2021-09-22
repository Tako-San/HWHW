#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CharBuf.hh"
#include "filesys.hh"
#include "trace.hh"
#include "tsl.hh"

int main(int argc, char *argv[])
{
  tll_set_log_lvl(TLL_ERR);
  if (2 != argc)
  {
    tll_error("USAGE: %s input_file\n", argv[0]);
    return tll_exit_code();
  }

  tll_verbose("Opening file: %s\n", argv[1]);

  CharBuf raw_data = {nullptr, 0};
  if (file_to_buf(argv[1], &raw_data) != 0)
    return tll_exit_code();

  StrArray parsed_data = tsl_split_lines(raw_data);
  for (size_t i = 0; i < parsed_data.size; ++i)
    printf("%.*s\n", (int)parsed_data.lines[i].size, parsed_data.lines[i].buf);

  qsort(parsed_data.lines, parsed_data.size, sizeof(CharBuf), tsl_cb_cmp);

  for (size_t i = 0; i < parsed_data.size; ++i)
    printf("%.*s\n", (int)parsed_data.lines[i].size, parsed_data.lines[i].buf);

  cb_destr(&raw_data);
  free(parsed_data.lines);
  return tll_exit_code();
}
