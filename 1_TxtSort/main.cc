#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tsl.hh"
#include "CharBuf.hh"

void print_usage(char name[]) { printf("USAGE: %s input_file\n", name); }
bool cl_parse(int argc) { return (argc == 2) ? true : false; }
long file_size(FILE *fp);


int main(int argc, char *argv[]) {
  if (!cl_parse(argc)) {
    print_usage(argv[0]);
    return 0;
  }

  char *filename = argv[1];
  FILE *fp = fopen(filename, "rb");
  if (nullptr == fp) {
    puts("Error while opening file.");
    puts("Exiting...");
    return 1;
  }

  size_t fsize = file_size(fp);
  CharBuf raw_data = {nullptr, 0};
  cb_init(&raw_data, fsize);

  fread(raw_data.buf, sizeof(char), file_size(fp), fp);
  printf("%s", raw_data.buf);

  fclose(fp);
  cb_destr(&raw_data);
  return 0;
}

long file_size(FILE *fp) {
  if (-1 == fseek(fp, 0L, SEEK_END))
    return -1;
  long res = ftell(fp);

  rewind(fp);
  return res;
}
