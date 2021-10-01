#ifndef __STACK_HH__
#define __STACK_HH__

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint64_t CanaryT;
bool stk_check_canaries(CanaryT can1, CanaryT can2, CanaryT owl1, CanaryT owl2);

const CanaryT stk_can1_val = 0xACABBACA;
const CanaryT stk_can2_val = 0xDEADBEEF;

const CanaryT stk_owl1_val = 0x89ABCDEF;
const CanaryT stk_owl2_val = 0xFACAFACA;

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
    type (*top)(const stk_##type *);                                                                                   \
    type (*pop)(stk_##type *);                                                                                         \
                                                                                                                       \
    stk_##type *(*destroy)(stk_##type *);                                                                              \
  };                                                                                                                   \
                                                                                                                       \
  struct stk_##type                                                                                                    \
  {                                                                                                                    \
    CanaryT can1_;                                                                                                     \
                                                                                                                       \
    size_t size_;                                                                                                      \
    size_t capacity_;                                                                                                  \
                                                                                                                       \
    CanaryT *owl1_;                                                                                                    \
    type *data_;                                                                                                       \
    CanaryT *owl2_;                                                                                                    \
                                                                                                                       \
    stk_functions_##type *functions_;                                                                                  \
                                                                                                                       \
    CanaryT can2_;                                                                                                     \
  };                                                                                                                   \
                                                                                                                       \
  bool stk_is_valid_##type(const stk_##type *stk)                                                                      \
  {                                                                                                                    \
    bool can = stk_check_canaries(stk->can1_, stk->can2_, *(stk->owl1_), *(stk->owl2_));                               \
    return can;                                                                                                        \
  }                                                                                                                    \
                                                                                                                       \
  bool stk_is_empty_##type(const stk_##type *stk)                                                                      \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    assert(stk_is_valid_##type(stk));                                                                                  \
    return (0 == stk->size_);                                                                                          \
  }                                                                                                                    \
                                                                                                                       \
  size_t stk_size_##type(const stk_##type *stk)                                                                        \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    assert(stk_is_valid_##type(stk));                                                                                  \
    return stk->size_;                                                                                                 \
  }                                                                                                                    \
                                                                                                                       \
  void stk_realloc_##type(stk_##type *stk, size_t new_cap)                                                             \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    assert(stk_is_valid_##type(stk));                                                                                  \
                                                                                                                       \
    CanaryT owl2 = *stk->owl2_; /* saving canary */                                                                    \
                                                                                                                       \
    size_t new_size = (new_cap * sizeof(type) - 1) / sizeof(CanaryT) + 1; /* size in canaries */                       \
    CanaryT *mem_ptr = (CanaryT *)reallocarray(stk->owl1_, new_size + 2, sizeof(CanaryT));                             \
    assert((mem_ptr != nullptr) && "Memory allocation error\n");                                                       \
                                                                                                                       \
    stk->owl1_ = (CanaryT *)(mem_ptr);                                                                                 \
    stk->owl2_ = (CanaryT *)(mem_ptr + 1 + new_size);                                                                  \
    *(stk->owl2_) = owl2;                                                                                              \
                                                                                                                       \
    stk->capacity_ = new_size * sizeof(CanaryT) / sizeof(type);                                                        \
    stk->data_ = (type *)(mem_ptr + 1);                                                                                \
  }                                                                                                                    \
                                                                                                                       \
  void stk_push_##type(stk_##type *stk, type elem)                                                                     \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    assert(stk_is_valid_##type(stk));                                                                                  \
                                                                                                                       \
    if (stk->size_ == stk->capacity_)                                                                                  \
      stk_realloc_##type(stk, 2 * stk->size_ + 1);                                                                     \
                                                                                                                       \
    assert((stk->data_ != nullptr) && "data array is nullptr");                                                        \
    stk->data_[stk->size_++] = elem;                                                                                   \
  }                                                                                                                    \
                                                                                                                       \
  type stk_pop_##type(stk_##type *stk)                                                                                 \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    assert(stk_is_valid_##type(stk));                                                                                  \
                                                                                                                       \
    size_t third_cap = stk->capacity_ / 3;                                                                             \
    if (stk->size_ < third_cap)                                                                                        \
      stk_realloc_##type(stk, third_cap);                                                                              \
                                                                                                                       \
    assert((stk->data_ != nullptr) && "data array is nullptr");                                                        \
    return stk->data_[--stk->size_];                                                                                   \
  }                                                                                                                    \
                                                                                                                       \
  type stk_top_##type(const stk_##type *stk)                                                                           \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    assert(stk_is_valid_##type(stk));                                                                                  \
    return stk->data_[stk->size_ - 1];                                                                                 \
  }                                                                                                                    \
                                                                                                                       \
  stk_##type *stk_destroy_##type(stk_##type *stk)                                                                      \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    assert(stk_is_valid_##type(stk));                                                                                  \
                                                                                                                       \
    free(stk->owl1_);                                                                                                  \
    stk->data_ = nullptr;                                                                                              \
    stk->size_ = 0;                                                                                                    \
    stk->capacity_ = 0;                                                                                                \
    return stk;                                                                                                        \
  }                                                                                                                    \
                                                                                                                       \
  stk_functions_##type stk_funcs_##type = {&stk_is_empty_##type, &stk_size_##type, &stk_push_##type,                   \
                                           &stk_top_##type,      &stk_pop_##type,  &stk_destroy_##type};               \
                                                                                                                       \
  void stk_init_##type(stk_##type *stk)                                                                                \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
                                                                                                                       \
    stk->can1_ = stk_can1_val;                                                                                         \
    stk->can2_ = stk_can2_val;                                                                                         \
                                                                                                                       \
    stk->size_ = 0;                                                                                                    \
    stk->capacity_ = 0;                                                                                                \
                                                                                                                       \
    stk->owl1_ = (CanaryT *)calloc(2, sizeof(CanaryT));                                                                \
    assert((stk->owl1_ != nullptr) && "Memory allocation error\n");                                                    \
    stk->owl2_ = stk->owl1_ + 1;                                                                                       \
                                                                                                                       \
    *(stk->owl1_) = stk_owl1_val;                                                                                      \
    *(stk->owl2_) = stk_owl2_val;                                                                                      \
                                                                                                                       \
    stk->functions_ = &stk_funcs_##type;                                                                               \
  }                                                                                                                    \
                                                                                                                       \
  stk_##type *stk_new_##type()                                                                                         \
  {                                                                                                                    \
    stk_##type *res = (stk_##type *)calloc(1, sizeof(stk_##type));                                                     \
    if (nullptr == res)                                                                                                \
      return nullptr;                                                                                                  \
                                                                                                                       \
    stk_init_##type(res);                                                                                              \
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
