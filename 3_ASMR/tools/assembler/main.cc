#include <cstdio>

#include <tsl.hh>

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::printf("USAGE: %s INPUT_NAME\n", argv[0]);
    return 1;
  }

  return 0;
}
