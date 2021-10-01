#include "stack.hh"

bool stk_check_canaries(CanaryT can1, CanaryT can2, CanaryT owl1, CanaryT owl2)
{
#ifdef STK_RELEASE_MODE
  return true;
#else
  return (can1 == stk_can1_val) && (can2 == stk_can2_val) && (owl1 == stk_owl1_val) && (owl2 == stk_owl2_val);
#endif
}

HashT stk_hash_calc(CanaryT can1, CanaryT can2, CanaryT *owl1p, CanaryT *owl2p, void *data, void *functions)
{
  return can1 * can2 * (HashT)owl1p * (HashT)owl2p * (HashT)data * (HashT)functions;
}
