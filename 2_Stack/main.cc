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
  stk_init(int, &testStack);

  for (size_t i = 0; i < 35; ++i)
    stk_push(&testStack, i);

  printf("Stack(int) size equals to %zu\n", stk_size(&testStack));

  while (!stk_is_empty(&testStack))
    printf("%d\n", stk_pop(&testStack));

  printf("Stack(int) size equals to %zu\n", stk_size(&testStack));
  stk_destroy(&testStack);

  puts("");

  Stack(double) *dStack = stk_new(double);
  stk_push(dStack, 12.5);
  stk_push(dStack, 24.5);
  stk_push(dStack, 9.12);
  stk_push(dStack, 32.51);

  while (!stk_is_empty(dStack))
    printf("%5.2f ", stk_pop(dStack));

  puts("");

  free(stk_destroy(dStack));
  return 0;
}
