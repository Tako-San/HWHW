#include <stdio.h>

#include "stack.hh"

bool stk_check_canaries(CanaryT can1, CanaryT can2, CanaryT owl1, CanaryT owl2)
{
#ifdef STK_RELEASE_MODE
  return true;
#else
  // puts(__func__);
  return (can1 == stk_can1_val) && (can2 == stk_can2_val) && (owl1 == stk_owl1_val) && (owl2 == stk_owl2_val);
#endif
}

HashT stk_hash_calc(const void *from_void, const void *to_void)
{
  assert(from_void != nullptr);
  assert(to_void != nullptr);

  const uint8_t *from = (const uint8_t *)from_void;
  const uint8_t *to = (const uint8_t *)to_void;

  HashT hash = 0;
  for (; from < to; ++from)
    hash += *from;

  return hash;
}

bool stk_check_hash(HashT hash, const void *from, const void *to)
{
  assert(from != nullptr);
  assert(to != nullptr);

#ifdef STK_RELEASE_MODE
  return true;
#else
  return (hash == stk_hash_calc(from, to));
#endif
}

const char * stk_print_errors(StkErrCode ec, FILE *fstream)
{
  switch (ec)
  {
  case STK_OK:
    fputs("stack is OK", fstream);
    break;
  case STK_IS_NULLPTR:
    fputs("pointer to stack is nullptr", fstream);
    break;
  case STK_MEMORY_ALLOCATION_ERROR:
    fputs("memory allocation error occurred", fstream);
    break;
  case STK_UNKNOWN_ERROR:
    fputs("unknown error occurred", fstream);
    break;
  case STK_CANARIES_DAMAGED:
    fputs("struct canaries has wrong value", fstream);
    break;
  case STK_OWLS_DAMAGED:
    fputs("data canaries has wrong value", fstream);
    break;
  case STK_STRUCT_HASH_DAMAGED:
    fputs("struct hash is not equal to calculated", fstream);
    break;
  case STK_DATA_HASH_DAMAGED:
    fputs("data hash is not equal to calculated", fstream);
    break;
  case STK_FUNC_HASH_DAMAGED:
    fputs("hash of the function struct is not equal to calculated", fstream);
    break;
  case STK_EMPTY:
    fputs("pop or top from empty stack happened", fstream);
    break;
  }
  return "hello";
}
