// doc/snippets/nextafter64.c
#include <stdio.h>
#include <fpnglib/constants64.h>
#include <fpnglib/float64.h>

int main(void)
{
  printf("%d\n",fpngl_nextafter64(1.0, 1L<<52) == 2.0);
}
