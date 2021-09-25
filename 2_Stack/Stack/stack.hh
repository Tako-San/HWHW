#ifndef __STACK_HH__
#define __STACK_HH__

#include <assert.h>
#include <stdlib.h>

#define define_stack(type)                                                                                             \
                                                                                                                       \
  struct stk_##type;                                                                                                   \
                                                                                                                       \
  struct stk_functions_##type                                                                                          \
  {                                                                                                                    \
    bool (*is_empty)(const stk_##type *);                                                                              \
    size_t (*size)(const stk_##type *);                                                                                \
                                                                                                                       \
    void (*push)(stk_##type *, type);                                                                                  \
    type (*pop)(stk_##type *);                                                                                         \
    type (*top)(const stk_##type *);                                                                                   \
                                                                                                                       \
    stk_##type *(*destroy)(stk_##type *);                                                                              \
  };                                                                                                                   \
                                                                                                                       \
  struct stk_##type                                                                                                    \
  {                                                                                                                    \
    size_t size_;                                                                                                      \
    size_t capacity_;                                                                                                  \
    type *data_;                                                                                                       \
    stk_functions_##type *functions_;                                                                                  \
  };                                                                                                                   \
                                                                                                                       \
  bool stk_is_empty_##type(const stk_##type *stk)                                                                      \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    return (0 == stk->size_);                                                                                          \
  }                                                                                                                    \
                                                                                                                       \
  size_t stk_size_##type(const stk_##type *stk)                                                                        \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    return stk->size_;                                                                                                 \
  }                                                                                                                    \
                                                                                                                       \
  void stk_push_##type(stk_##type *stk, type elem)                                                                     \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
                                                                                                                       \
    if (stk->size_ == stk->capacity_)                                                                                  \
    {                                                                                                                  \
      stk->capacity_ = stk->size_ * 2 + 1;                                                                             \
      stk->data_ = (type *)reallocarray(stk->data_, stk->capacity_, sizeof(type));                                     \
    }                                                                                                                  \
                                                                                                                       \
    assert((stk->data_ != nullptr) && "data array is nullptr");                                                        \
    stk->data_[stk->size_++] = elem;                                                                                   \
  }                                                                                                                    \
                                                                                                                       \
  type stk_pop_##type(stk_##type *stk)                                                                                 \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    return stk->data_[--stk->size_];                                                                                   \
  }                                                                                                                    \
                                                                                                                       \
  type stk_top_##type(const stk_##type *stk)                                                                           \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    return stk->data_[stk->size_ - 1];                                                                                 \
  }                                                                                                                    \
                                                                                                                       \
  stk_##type *stk_destroy_##type(stk_##type *stk)                                                                      \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
                                                                                                                       \
    free(stk->data_);                                                                                                  \
    stk->data_ = nullptr;                                                                                              \
    stk->size_ = 0;                                                                                                    \
    stk->capacity_ = 0;                                                                                                \
    return stk;                                                                                                        \
  }                                                                                                                    \
                                                                                                                       \
  stk_functions_##type stk_funcs_##type = {&stk_is_empty_##type, &stk_size_##type, &stk_push_##type,                   \
                                           &stk_pop_##type,      &stk_top_##type,  &stk_destroy_##type};               \
                                                                                                                       \
  void stk_init_##type(stk_##type *stk)                                                                                \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    stk->capacity_ = 0;                                                                                                \
    stk->size_ = 0;                                                                                                    \
    stk->data_ = nullptr;                                                                                              \
    stk->functions_ = &stk_funcs_##type;                                                                               \
  }                                                                                                                    \
                                                                                                                       \
  stk_##type *stk_new_##type()                                                                                         \
  {                                                                                                                    \
    stk_##type *res = (stk_##type *)calloc(1, sizeof(stk_##type));                                                     \
    if (nullptr == res)                                                                                                \
      return nullptr;                                                                                                  \
                                                                                                                       \
    stk_init_##type(res);                                                                                                     \
    return res;                                                                                                        \
  }

#define Stack(type) stk_##type

#define stk_new(type) stk_new_##type()
#define stk_init(type, stack) stk_init_##type(stack)
#define stk_destroy(stack) (stack)->functions_->destroy(stack)

#define stk_is_empty(stack) (stack)->functions_->is_empty(stack)
#define stk_size(stack) (stack)->functions_->size(stack)

#define stk_push(stack, elem) (stack)->functions_->push(stack, elem)
#define stk_pop(stack) (stack)->functions_->pop(stack)
#define stk_top(stack) (stack)->functions_->top(stack)

#endif // __STACK_HH__
