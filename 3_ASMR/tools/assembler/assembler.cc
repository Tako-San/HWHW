#include <filesys.hh>
#include <trace.hh>
#include <tsl.hh>

#include "assembler.hh"

void assembly(StrArray input_buf, int32_t *output_buf);

int assembler_main(const char *input_file, const char *output_file)
{
  CharBuf raw_input{};
  int ftb_res = file_to_buf(input_file, &raw_input);
  if (ftb_res != 0)
  {
    tll_error("Error while opening file %s\n", input_file);
    return ftb_res;
  }

  StrArray sep_input = tsl_split_lines(raw_input);

  int32_t *output_buf = (int32_t *)calloc(sep_input.size, sizeof(int32_t));
  if (nullptr == output_buf)
  {
    tll_error("Output buffer allocation error\n");
    return 1;
  }

  assembly(sep_input, output_buf);
  sa_print(sep_input, stdout);

  sa_destr(&sep_input);
  cb_destr(&raw_input);

  return 0;
}

void assembly(StrArray input_buf, int32_t *output_buf)
{
  for (size_t i = 0, j = 0; i < input_buf.size; ++i)
  {
    // output_buf[j] = ASMR::get_opcode(input_buf.lines[i]);
    // if (output_buf[j] != ASMR::EMPTY_OP)
    //   ++j;
  }
}
