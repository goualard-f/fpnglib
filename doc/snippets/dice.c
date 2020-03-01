// doc/snippets/dice.c
#include <stdio.h>
#include <fpnglib/mt19937ar.h>
#include <fpnglib/irng_t.h>
#include <fpnglib/irange.h>

const uint32_t seed = 13;

int main(void)
{
  fpngl_irng_t *irng = fpngl_irng_new32(fpngl_mt19937v32(seed));
  printf("%u\n",fpngl_ubound32(irng,6) + 1);
  fpngl_irng_delete(irng);
}
