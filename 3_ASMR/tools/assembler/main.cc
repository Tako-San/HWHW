#include <trace.hh>

#include "assembler.hh"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    tll_error("USAGE: %s INPUT_NAME\n", argv[0]);
    return 1;
  }

  return assembler_main(argv[1], nullptr);
}
