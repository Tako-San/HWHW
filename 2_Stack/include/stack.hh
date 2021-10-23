#ifndef __STACK_HH__
#define __STACK_HH__

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>

typedef uint64_t HashT;
typedef uint64_t CanaryT;

enum StkErrCode
{
  STK_OK = 0,
  STK_IS_NULLPTR,
  STK_MEMORY_ALLOCATION_ERROR,
  STK_UNKNOWN_ERROR,
  STK_CANARIES_DAMAGED,
  STK_OWLS_DAMAGED,
  STK_STRUCT_HASH_DAMAGED,
  STK_DATA_HASH_DAMAGED,
  STK_FUNC_HASH_DAMAGED,
  STK_EMPTY
};

bool stk_check_canaries(CanaryT can1, CanaryT can2, CanaryT owl1, CanaryT owl2);

bool stk_check_hash(HashT hash, const void *from, const void *to);
HashT stk_hash_calc(const void *from_void, const void *to_void);

void stk_print_errors(StkErrCode ec);

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
    bool (*is_empty)(const stk_##type *, StkErrCode *);                                                                \
    size_t (*size)(const stk_##type *, StkErrCode *);                                                                  \
                                                                                                                       \
    void (*push)(stk_##type *, type, StkErrCode *);                                                                    \
    type (*top)(const stk_##type *, StkErrCode *);                                                                     \
    type (*pop)(stk_##type *, StkErrCode *);                                                                           \
    void (*dump)(const stk_##type *);                                                                                  \
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
    HashT data_hash_;                                                                                                  \
    HashT func_hash_;                                                                                                  \
    HashT struct_hash_;                                                                                                \
                                                                                                                       \
    CanaryT can2_;                                                                                                     \
  };                                                                                                                   \
                                                                                                                       \
  StkErrCode stk_is_valid_##type(const stk_##type *stk)                                                                \
  {                                                                                                                    \
    if (nullptr == stk)                                                                                                \
      return STK_IS_NULLPTR;                                                                                           \
                                                                                                                       \
    if (!stk_check_canaries(stk->can1_, stk->can2_, *(stk->owl1_), *(stk->owl2_)))                                     \
      return STK_CANARIES_DAMAGED;                                                                                     \
    if (!stk_check_hash(stk->data_hash_, stk->data_, stk->data_ + stk->size_))                                         \
      return STK_DATA_HASH_DAMAGED;                                                                                    \
    if (!stk_check_hash(stk->func_hash_, stk->functions_, stk->functions_ + sizeof(stk_functions_##type)))             \
      return STK_FUNC_HASH_DAMAGED;                                                                                    \
    if (!stk_check_hash(stk->struct_hash_, &(stk->size_), &(stk->struct_hash_)))                                       \
      return STK_STRUCT_HASH_DAMAGED;                                                                                  \
                                                                                                                       \
    return STK_OK;                                                                                                     \
  }                                                                                                                    \
                                                                                                                       \
  void stk_hash_recalc_##type(stk_##type *stk)                                                                         \
  {                                                                                                                    \
    stk->data_hash_ = stk_hash_calc(stk->data_, stk->data_ + stk->size_);                                              \
    stk->struct_hash_ = stk_hash_calc(&(stk->size_), &(stk->struct_hash_));                                            \
  }                                                                                                                    \
                                                                                                                       \
  bool stk_is_empty_##type(const stk_##type *stk, StkErrCode *ec)                                                      \
  {                                                                                                                    \
    *ec = stk_is_valid_##type(stk);                                                                                    \
    if (*ec != STK_OK)                                                                                                 \
      return true;                                                                                                     \
                                                                                                                       \
    return (0 == stk->size_);                                                                                          \
  }                                                                                                                    \
                                                                                                                       \
  size_t stk_size_##type(const stk_##type *stk, StkErrCode *ec)                                                        \
  {                                                                                                                    \
    *ec = stk_is_valid_##type(stk);                                                                                    \
    if (*ec != STK_OK)                                                                                                 \
      return 0;                                                                                                        \
                                                                                                                       \
    return stk->size_;                                                                                                 \
  }                                                                                                                    \
                                                                                                                       \
  StkErrCode stk_realloc_##type(stk_##type *stk, size_t new_cap)                                                       \
  {                                                                                                                    \
    StkErrCode ec = stk_is_valid_##type(stk);                                                                          \
    if (ec != STK_OK)                                                                                                  \
      return ec;                                                                                                       \
                                                                                                                       \
    CanaryT owl2 = *stk->owl2_; /* saving canary */                                                                    \
                                                                                                                       \
    size_t new_size = (new_cap * sizeof(type) - 1) / sizeof(CanaryT) + 1; /* size in canaries */                       \
    CanaryT *mem_ptr = (CanaryT *)reallocarray(stk->owl1_, new_size + 2, sizeof(CanaryT));                             \
    if (nullptr == mem_ptr)                                                                                            \
      return STK_MEMORY_ALLOCATION_ERROR;                                                                              \
                                                                                                                       \
    stk->owl1_ = mem_ptr;                                                                                              \
    stk->owl2_ = mem_ptr + 1 + new_size;                                                                               \
    *(stk->owl2_) = owl2;                                                                                              \
                                                                                                                       \
    stk->capacity_ = new_size * sizeof(CanaryT) / sizeof(type);                                                        \
    stk->data_ = (type *)(mem_ptr + 1);                                                                                \
    stk_hash_recalc_##type(stk);                                                                                       \
    return STK_OK;                                                                                                     \
  }                                                                                                                    \
                                                                                                                       \
  void stk_push_##type(stk_##type *stk, type elem, StkErrCode *ec)                                                     \
  {                                                                                                                    \
    *ec = stk_is_valid_##type(stk);                                                                                    \
    if (*ec != STK_OK)                                                                                                 \
      return;                                                                                                          \
                                                                                                                       \
    if (stk->size_ == stk->capacity_)                                                                                  \
    {                                                                                                                  \
      *ec = stk_realloc_##type(stk, 2 * stk->size_ + 1);                                                               \
      if (*ec != STK_OK)                                                                                               \
        return;                                                                                                        \
    }                                                                                                                  \
                                                                                                                       \
    assert((stk->data_ != nullptr) && "data array is nullptr");                                                        \
    stk->data_[stk->size_++] = elem;                                                                                   \
    stk_hash_recalc_##type(stk);                                                                                       \
  }                                                                                                                    \
                                                                                                                       \
  type stk_pop_##type(stk_##type *stk, StkErrCode *ec)                                                                 \
  {                                                                                                                    \
    *ec = stk_is_valid_##type(stk);                                                                                    \
    if (*ec != STK_OK)                                                                                                 \
      return {};                                                                                                       \
                                                                                                                       \
    if (stk->size_ == 0)                                                                                               \
    {                                                                                                                  \
      *ec = STK_EMPTY;                                                                                                 \
      return {};                                                                                                       \
    }                                                                                                                  \
                                                                                                                       \
    size_t third_cap = stk->capacity_ / 3;                                                                             \
    if (stk->size_ < third_cap)                                                                                        \
    {                                                                                                                  \
      *ec = stk_realloc_##type(stk, third_cap);                                                                        \
      if (*ec != STK_OK)                                                                                               \
        return {};                                                                                                     \
                                                                                                                       \
      if (nullptr == stk->data_)                                                                                       \
      {                                                                                                                \
        *ec = STK_MEMORY_ALLOCATION_ERROR;                                                                             \
        return {};                                                                                                     \
      }                                                                                                                \
    }                                                                                                                  \
                                                                                                                       \
    stk->size_ -= 1;                                                                                                   \
    stk_hash_recalc_##type(stk);                                                                                       \
    return stk->data_[stk->size_];                                                                                     \
  }                                                                                                                    \
                                                                                                                       \
  type stk_top_##type(const stk_##type *stk, StkErrCode *ec)                                                           \
  {                                                                                                                    \
    *ec = stk_is_valid_##type(stk);                                                                                    \
    if (*ec != STK_OK)                                                                                                 \
      return {};                                                                                                       \
                                                                                                                       \
    if (stk->size_ == 0)                                                                                               \
    {                                                                                                                  \
      *ec = STK_EMPTY;                                                                                                 \
      return {};                                                                                                       \
    }                                                                                                                  \
                                                                                                                       \
    return stk->data_[stk->size_ - 1];                                                                                 \
  }                                                                                                                    \
                                                                                                                       \
  void stk_print_elem_##type(const type *elem_ptr);                                                                    \
                                                                                                                       \
  void stk_dump_##type(const stk_##type *stk)                                                                          \
  {                                                                                                                    \
    printf("\n============================Dump of %s stack============================\n", #type);                     \
    puts("");                                                                                                          \
    printf("Dear sir, your stack contains %zu elements and may fit %zu at the moment.\n", stk->size_, stk->capacity_); \
    puts("");                                                                                                          \
    puts("Let's talk about birds!");                                                                                   \
    printf("It's struct canaries values: 0x%lX for first and 0x%lX for second.\n", stk->can1_, stk->can2_);            \
    printf("It's data canaries values: 0x%lX for first and 0x%lX for second.\n", *stk->owl1_, *stk->owl2_);            \
    puts("");                                                                                                          \
    puts("We need to discuss hash too.");                                                                              \
    printf("Struct hash: 0x%lX\n", stk->struct_hash_);                                                                 \
    printf("Data hash: 0x%lX\n", stk->data_hash_);                                                                     \
    printf("Func hash: 0x%lX\n", stk->func_hash_);                                                                     \
    puts("");                                                                                                          \
    puts("Stack data. Finally.");                                                                                      \
    for (size_t i = 0; i < stk->size_; ++i)                                                                            \
    {                                                                                                                  \
      stk_print_elem_##type(stk->data_ + i);                                                                           \
      puts("");                                                                                                        \
    }                                                                                                                  \
    puts("");                                                                                                          \
    puts("============================================================================\n");                            \
  }                                                                                                                    \
                                                                                                                       \
  stk_##type *stk_destroy_##type(stk_##type *stk)                                                                      \
  {                                                                                                                    \
    free(stk->owl1_);                                                                                                  \
    stk->data_ = nullptr;                                                                                              \
    stk->size_ = 0;                                                                                                    \
    stk->capacity_ = 0;                                                                                                \
    stk_hash_recalc_##type(stk);                                                                                       \
    return stk;                                                                                                        \
  }                                                                                                                    \
                                                                                                                       \
  stk_functions_##type stk_funcs_##type = {                                                                            \
      &stk_is_empty_##type, &stk_size_##type, &stk_push_##type,   &stk_top_##type,                                     \
      &stk_pop_##type,      &stk_dump_##type, &stk_destroy_##type};                                                    \
                                                                                                                       \
  void stk_init_##type(stk_##type *stk, StkErrCode *ec)                                                                \
  {                                                                                                                    \
    if (nullptr == stk)                                                                                                \
    {                                                                                                                  \
      *ec = STK_IS_NULLPTR;                                                                                            \
      return;                                                                                                          \
    }                                                                                                                  \
                                                                                                                       \
    stk->can1_ = stk_can1_val;                                                                                         \
    stk->can2_ = stk_can2_val;                                                                                         \
                                                                                                                       \
    stk->size_ = 0;                                                                                                    \
    stk->capacity_ = 0;                                                                                                \
                                                                                                                       \
    stk->owl1_ = (CanaryT *)calloc(2, sizeof(CanaryT));                                                                \
    if (stk->owl1_ == nullptr)                                                                                         \
    {                                                                                                                  \
      *ec = STK_MEMORY_ALLOCATION_ERROR;                                                                               \
      return;                                                                                                          \
    }                                                                                                                  \
                                                                                                                       \
    stk->owl2_ = stk->owl1_ + 1;                                                                                       \
                                                                                                                       \
    *(stk->owl1_) = stk_owl1_val;                                                                                      \
    *(stk->owl2_) = stk_owl2_val;                                                                                      \
                                                                                                                       \
    stk->functions_ = &stk_funcs_##type;                                                                               \
                                                                                                                       \
    stk->data_hash_ = stk_hash_calc(stk->data_, stk->data_ + stk->size_);                                              \
    stk->func_hash_ = stk_hash_calc(stk->functions_, stk->functions_ + sizeof(stk_functions_##type));                  \
    stk->struct_hash_ = stk_hash_calc(&(stk->size_), &(stk->struct_hash_));                                            \
  }                                                                                                                    \
                                                                                                                       \
  stk_##type *stk_new_##type(StkErrCode *ec)                                                                           \
  {                                                                                                                    \
    stk_##type *res = (stk_##type *)calloc(1, sizeof(stk_##type));                                                     \
    if (nullptr == res)                                                                                                \
    {                                                                                                                  \
      *ec = STK_MEMORY_ALLOCATION_ERROR;                                                                               \
      return nullptr;                                                                                                  \
    }                                                                                                                  \
                                                                                                                       \
    stk_init_##type(res, ec);                                                                                          \
    return res;                                                                                                        \
  }

#define Stack(type) stk_##type

#define stk_new(type, err_code) stk_new_##type(err_code)
#define stk_init(type, stack, err_code) stk_init_##type(stack, err_code)
#define stk_destroy(stack) (stack)->functions_->destroy(stack)

#define stk_is_empty(stack, err_code) (stack)->functions_->is_empty(stack, err_code)
#define stk_size(stack, err_code) (stack)->functions_->size(stack, err_code)
#define stk_dump(stack) (stack)->functions_->dump(stack)

#define stk_push(stack, elem, err_code) (stack)->functions_->push(stack, elem, err_code)
#define stk_pop(stack, err_code) (stack)->functions_->pop(stack, err_code)
#define stk_top(stack, err_code) (stack)->functions_->top(stack, err_code)

#endif // __STACK_HH__
