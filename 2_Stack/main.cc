#include "stack.hh"
#include <stdio.h>

define_stack(int);
define_stack(double);

int main()
{
  Stack(int) testStack{};
  stk_init(int, &testStack);

  stk_push(&testStack, 1);
  stk_push(&testStack, 2);
  stk_push(&testStack, 3);
  stk_push(&testStack, 4);

  while (!stk_is_empty(&testStack))
    printf("%5d ", stk_pop(&testStack));

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

  stk_destroy(dStack);
  free(dStack);

  return 0;
}
