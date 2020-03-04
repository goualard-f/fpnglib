// doc/snippets/subnormal.c
#include <stdio.h>
#include <fpnglib/float64.h>
#include <fpnglib/mt19937-64.h>

const uint64_t seed = 42;

int main(void)
{
  fpngl_irng_t *irng = fpngl_irng_new64(fpngl_mt19937v64(seed));
  printf("Random denormal: %g\n",fpngl_denormal64(irng));
  printf("Random normal: %g\n",fpngl_normal64(irng));
  fpngl_irng_delete(irng);
}
