// doc/snippets/nan.c
#include <stdio.h>
#include <fpnglib/constants32.h>
#include <fpnglib/constants64.h>

int main(void)
{
  printf("Single precision NaN: %g\n",fpngl_NaN32);
  printf("Double precision NaN: %g\n",fpngl_NaN64);
}
