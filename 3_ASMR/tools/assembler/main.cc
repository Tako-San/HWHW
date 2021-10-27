#include <cstdio>

#include "filesys.hh"
#include "trace.hh"
#include "tsl.hh"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::printf("USAGE: %s INPUT_NAME\n", argv[0]);
    return 1;
  }

  CharBuf raw_input{};
  int ftb_res = file_to_buf(argv[1], &raw_input);
  if (ftb_res != 0)
  {
    tll_error("Error while opening file %s\n", argv[1]);
    return ftb_res;
  }

  StrArray sep_input = tsl_split_lines(raw_input);

  sa_print(sep_input, stdout);

  sa_destr(&sep_input);
  cb_destr(&raw_input);
  return 0;
}
