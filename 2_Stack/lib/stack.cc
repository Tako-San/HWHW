#include <stdio.h>

#include "stack.hh"

typedef uint8_t PoisonT;

FILE *STK_ERR = stderr;
PoisonT POISON_VAL = 0xFC;

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

const char * stk_err_descr(StkErrCode ec)
{
  switch (ec)
  {
  case STK_OK:
    return "stack is OK";
  case STK_IS_NULLPTR:
    return "pointer to stack is nullptr";
  case STK_MEMORY_ALLOCATION_ERROR:
    return "memory allocation error occurred";
  case STK_UNKNOWN_ERROR:
    return "unknown error occurred";
  case STK_CANARIES_DAMAGED:
    return "struct canaries has wrong value";
  case STK_OWLS_DAMAGED:
    return "data canaries has wrong value";
  case STK_STRUCT_HASH_DAMAGED:
    return "struct hash is not equal to calculated";
  case STK_DATA_HASH_DAMAGED:
    return "data hash is not equal to calculated";
  case STK_FUNC_HASH_DAMAGED:
    return "hash of the function struct is not equal to calculated";
  case STK_EMPTY:
    return "pop or top from empty stack happened";
  default:
    return "really unknown error";
  }
}

void fill_w_poison(void * from_void, void * to_void)
{
  assert(from_void != nullptr);
  assert(to_void != nullptr);

  PoisonT *from = (PoisonT *)from_void;
  PoisonT *to = (PoisonT *)to_void;

  for (; from < to; ++from)
    *from = POISON_VAL;
}
