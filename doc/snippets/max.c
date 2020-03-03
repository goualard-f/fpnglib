// doc/snippets/max.c
#include <stdio.h>
#include <fpnglib/constants32.h>
#include <fpnglib/constants64.h>

int main(void)
{
  printf("Single precision largest float: %g\n",fpngl_max32);
  printf("Double precision largest float: %g\n",fpngl_max64);
}
