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

void tqs_swap(void *l, void *r, size_t size)
{
  uint8_t tmp[size] = {};

  memcpy(&tmp, l, size);
  memcpy(l, r, size);
  memcpy(r, &tmp, size);
}

void tqsort_impl(void *void_base, size_t size, tqs_cmp compar, int l, int r)
{
  uint8_t *base = (uint8_t *)void_base;
  int i = l, j = r;
  int m = (l + r) / 2;

  uint8_t *pp[3] = {base + l * size, base + r * size, base + m * size};
  if (compar((void *)pp[0], (void *)pp[1]) < 0)
    tqs_swap_ui8(&pp[0], &pp[1]);
  if (compar((void *)pp[1], (void *)pp[2]) < 0)
    tqs_swap_ui8(&pp[1], &pp[2]);
  if (compar((void *)pp[0], (void *)pp[1]) < 0)
    tqs_swap_ui8(&pp[0], &pp[1]);

  uint8_t *p = pp[1];
  while (i <= j)
  {
    while (compar((void *)p, (void *)(base + i * size)) > 0)
      i++;
    while (compar((void *)p, (void *)(base + j * size)) < 0)
      j--;
    if (i <= j)
    {
      tqs_swap(base + i * size, base + j * size, size);
      i++;
      j--;
    }
  }
  if (l < j)
    tqsort_impl(void_base, size, compar, l, j);
  if (i < r)
    tqsort_impl(void_base, size, compar, i, r);
}

void tqsort(void *base, size_t nmemb, size_t size, tqs_cmp compar)
{
  tqsort_impl(base, size, compar, 0, nmemb - 1);
}
