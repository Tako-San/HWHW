#include <stdio.h>

#include "stack.hh"

define_stack(int);
void stk_print_elem(int)(const int *elem_ptr)
{
  printf("%d", *elem_ptr);
}

define_stack(double);
void stk_print_elem(double)(const double *elem_ptr)
{
  printf("%le", *elem_ptr);
}

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

  stk_dump(&testStack, stdout);
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

  stk_dump(dStack, stdout);

  while (!stk_is_empty(dStack, &err_code))
    stk_pop(dStack, &err_code);

  free(stk_destroy(dStack));

  dStack = stk_new(double, &err_code);
  stk_push(dStack, 1, &err_code);
  stk_dump(dStack, stdout);
  printf("pop1: %lf\n", stk_pop(dStack, &err_code));
  printf("pop2: %lf\n", stk_pop(dStack, &err_code));
  stk_err_descr(err_code);
  free(stk_destroy(dStack));

  return 0;
}
