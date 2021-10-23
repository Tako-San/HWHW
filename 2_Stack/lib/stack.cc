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
  const uint8_t *from = (const uint8_t *)from_void;
  const uint8_t *to = (const uint8_t *)to_void;

  HashT hash = 0;
  for (; from < to; ++from)
    hash += *from;

  return hash;
}

bool stk_check_hash(HashT hash, const void *from, const void *to)
{
#ifdef STK_RELEASE_MODE
  return true;
#else
  bool res = (hash == stk_hash_calc(from, to));
  if (!res)
    printf("Hashes are not equal\n");

  return hash == stk_hash_calc(from, to);
#endif
}
