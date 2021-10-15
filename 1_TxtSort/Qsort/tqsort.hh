#ifndef __TQSORT__
#define __TQSORT__

#include <stdio.h>

typedef int (*tqs_cmp)(const void *, const void *);

void tqsort(void *base, size_t nmemb, size_t size, tqs_cmp compar);

#endif // __TQSORT__
