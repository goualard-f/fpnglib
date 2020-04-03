// doc/snippets/significand.c
#include <stdio.h>
#include <math.h>
#include <fpnglib/constants32.h>
#include <fpnglib/constants64.h>

int main(void)
{
  printf("Number of bits with single precision: %u\n",
				 fpngl_t32);
  printf("Number of bits with double precision: %u\n",
         fpngl_t64);
  printf("Number of digits with single precision: %u\n",
         (uint32_t)trunc(fpngl_t32*log10(2)));
  printf("Number of digits with double precision: %u\n",
         (uint32_t)trunc(fpngl_t64*log10(2)));
}
