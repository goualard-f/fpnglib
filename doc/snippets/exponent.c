// doc/snippets/exponent.c
#include <stdio.h>
#include <math.h>
#include <fpnglib/constants32.h>
#include <fpnglib/constants64.h>

int main(void)
{
  printf("Single precision exponent in [%d, %d]\n",
         fpngl_emin32,fpngl_emax32);
  printf("Double precision exponent in [%d, %d]\n",
         fpngl_emin64,fpngl_emax64);
}
