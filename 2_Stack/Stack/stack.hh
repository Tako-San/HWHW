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
    type (*top)(stk_##type *);                                                                                         \
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
    assert((stk->data_ != nullptr) && "data array is nullptr");                                                          \
    stk->data_[stk->size_++] = elem;                                                                                   \
  }                                                                                                                    \
                                                                                                                       \
  type stk_pop_##type(stk_##type *stk)                                                                                 \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    return stk->data_[--stk->size_];                                                                                   \
  }                                                                                                                    \
                                                                                                                       \
  type stk_top_##type(stk_##type *stk)                                                                                 \
  {                                                                                                                    \
    assert(stk != nullptr);                                                                                            \
    return stk->data_[--stk->size_];                                                                                   \
  }                                                                                                                    \
                                                                                                                       \
  stk_##type *stk_destroy_##type(stk_##type *stk)                                                                      \
  {                                                                                                                    \
    if (nullptr == stk)                                                                                                \
      return nullptr;                                                                                                  \
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
  stk_##type *new_stk_##type()                                                                                         \
  {                                                                                                                    \
    stk_##type *res = (stk_##type *)calloc(1, sizeof(stk_##type));                                                     \
    if (nullptr == res)                                                                                                \
      return nullptr;                                                                                                  \
                                                                                                                       \
    res->capacity_ = 0;                                                                                                \
    res->size_ = 0;                                                                                                    \
    res->data_ = nullptr;                                                                                              \
    res->functions_ = &stk_funcs_##type;                                                                               \
    return res;                                                                                                        \
  }

#define stack(type) stk_##type

#define stk_new(type) new_stk_##type()
#define stk_destroy(collection) collection->functions_->destroy(collection)

#define stk_is_empty(collection) collection->functions_->is_empty(collection)
#define stk_size(collection) collection->functions_->size(collection)

#define stk_push(collection, elem) collection->functions_->push(collection, elem)
#define stk_pop(collection) collection->functions_->pop(collection)
#define stk_top(collection) collection->functions_->top(collection)

#endif // __STACK_HH__
