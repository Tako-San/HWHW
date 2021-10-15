#include <stdint.h>
#include <string.h>
#include <utility>

#include "tqsort.hh"

void tqs_swap_ui8(uint8_t **l, uint8_t **r)
{
  uint8_t *tmp = *l;
  *l = *r;
  *r = tmp;
}

void tqs_swap(void *left, void *right, size_t size)
{
  uint8_t tmp[size] = {};

  memcpy(&tmp, left, size);
  memcpy(left, right, size);
  memcpy(right, &tmp, size);
}

void tqsort_impl(void *void_base, size_t size, tqs_cmp compar, int left, int right)
{
  uint8_t *base = (uint8_t *)void_base;
  int l_idx = left, r_idx = right;
  int pivot = (left + right) / 2;

  uint8_t *pp[3] = {base + left * size, base + right * size, base + pivot * size};
  if (compar((void *)pp[0], (void *)pp[1]) < 0)
    tqs_swap_ui8(&pp[0], &pp[1]);
  if (compar((void *)pp[1], (void *)pp[2]) < 0)
    tqs_swap_ui8(&pp[1], &pp[2]);
  if (compar((void *)pp[0], (void *)pp[1]) < 0)
    tqs_swap_ui8(&pp[0], &pp[1]);

  uint8_t *p = pp[1];
  while (l_idx <= r_idx)
  {
    while (compar((void *)p, (void *)(base + l_idx * size)) > 0)
      l_idx++;
    while (compar((void *)p, (void *)(base + r_idx * size)) < 0)
      r_idx--;
    if (l_idx <= r_idx)
    {
      tqs_swap(base + l_idx * size, base + r_idx * size, size);
      l_idx++;
      r_idx--;
    }
  }
  if (left < r_idx)
    tqsort_impl(void_base, size, compar, left, r_idx);
  if (l_idx < right)
    tqsort_impl(void_base, size, compar, l_idx, right);
}

void tqsort(void *base, size_t nmemb, size_t size, tqs_cmp compar)
{
  tqsort_impl(base, size, compar, 0, nmemb - 1);
}
