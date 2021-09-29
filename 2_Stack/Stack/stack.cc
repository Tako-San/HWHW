#include "stack.hh"

bool stk_check_canaries(CanaryT can1, CanaryT can2, CanaryT owl1, CanaryT owl2)
{
#ifdef STK_RELEASE_MODE
  return true;
#else
  return (can1 == stk_can1_val) && (can2 == stk_can2_val) && (owl1 == stk_owl1_val) && (owl2 == stk_owl2_val);
#endif
}

