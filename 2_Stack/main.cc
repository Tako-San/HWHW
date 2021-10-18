#include <stdio.h>

#include "stack.hh"

define_stack(int);
define_stack(double);

int test();

int main()
{
  return test();
}

int test()
{
  Stack(int) testStack{};
  StkErrCode err_code = STK_OK;
  stk_init(int, &testStack, &err_code);

  for (int i = 0; i < 35; ++i)
    stk_push(&testStack, i, &err_code);

  printf("Stack(int) size equals to %zu\n", stk_size(&testStack, &err_code));

  while (!stk_is_empty(&testStack, &err_code))
    printf("%d\n", stk_pop(&testStack, &err_code));

  printf("Stack(int) size equals to %zu\n", stk_size(&testStack, &err_code));
  stk_destroy(&testStack);

  puts("");

  Stack(double) *dStack = stk_new(double, &err_code);
  stk_push(dStack, 12.5, &err_code);
  stk_push(dStack, 24.5, &err_code);
  stk_push(dStack, 9.12, &err_code);
  stk_push(dStack, 32.51, &err_code);

  while (!stk_is_empty(dStack, &err_code))
    printf("%5.2f ", stk_pop(dStack, &err_code));

  puts("");

  free(stk_destroy(dStack));

  dStack = stk_new(double, &err_code);
  stk_push(dStack, 1, &err_code);
  printf("pop1: %lf", stk_pop(dStack, &err_code)); 
  printf("pop2: %lf", stk_pop(dStack, &err_code)); 
  return 0;
}
