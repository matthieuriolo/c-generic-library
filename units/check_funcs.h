#ifndef _CHECK_FUNCS_H_
#define _CHECK_FUNCS_H_
#include <stdio.h>
int32_t
intcmp(const void *a, const void *b,size_t x UNUSED)
{
  if ((*(const int *) a) < (*(const int *) b)) {
    return -1;
  } else if ((*(const int *) a) > (*(const int *) b)) {
    return 1;
  } else {
    return 0;
  }
}

void
print_int(const void *a)
{
  printf("%d ", (*(const int *) a));
}

void *
ckalloc(size_t size)
{
  void *ptr;

  do {
    ptr = malloc(size);
  }
  while (!ptr);
  return ptr;
}

void
ckfree(void *ptr)
{
  free(ptr);
}
#endif // _CHECK_FUNCS_H_
