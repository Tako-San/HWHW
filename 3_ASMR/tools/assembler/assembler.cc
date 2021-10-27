#include <filesys.hh>
#include <trace.hh>
#include <tsl.hh>

#include "assembler.hh"

int assembler_main(const char * input_file, const char * output_file)
{
  CharBuf raw_input{};
  int ftb_res = file_to_buf(input_file, &raw_input);
  if (ftb_res != 0)
  {
    tll_error("Error while opening file %s\n", input_file);
    return ftb_res;
  }

  StrArray sep_input = tsl_split_lines(raw_input);

  sa_print(sep_input, stdout);

  sa_destr(&sep_input);
  cb_destr(&raw_input);

  return 0;
}
