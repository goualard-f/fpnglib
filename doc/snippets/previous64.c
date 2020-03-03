// doc/snippets/previous64.c
#include <stdio.h>
#include <fpnglib/constants64.h>
#include <fpnglib/float64.h>

int main(void)
{
  printf("%d\n",fpngl_previous64(fpngl_mu64, 2) == -fpngl_mu64);
}
