#include <stdio.h>
#include "stack.hh"

define_stack(int)
define_stack(double)

int main()
{
  stack(int) * testStack = stk_new(int);
  stk_push(testStack, 1);
  stk_push(testStack, 2);
  stk_push(testStack, 3);
  stk_push(testStack, 4);

  while (!stk_is_empty(testStack))
    printf("%d\n", stk_pop(testStack));

  stk_destroy(testStack);
  free(testStack);

  puts("");

  stack(double) * dStack = stk_new(double);
  stk_push(dStack, 12.5);
  stk_push(dStack, 24.5);
  stk_push(dStack, 9.12);

  while (!stk_is_empty(dStack))
    printf("%.2f\n", stk_pop(dStack));

  stk_destroy(dStack);
  free(dStack);

  return 0;
}