// doc/snippets/float64.c
#include <stdio.h>
#include <fpnglib/constants64.h>
#include <fpnglib/float64.h>
#include <fpnglib/mt19937-64.h>

const uint64_t seed = 13;

int main(void)
{
  fpngl_irng_t *irng = fpngl_irng_new64(fpngl_mt19937v64(seed));
  for (uint32_t i = 0; i < 10; ++i) {
    printf("%g\n",fpngl_float64(irng, fpngl_positive, 1024, 1024,
                                fpngl_minfrac64, fpngl_maxfrac64,
                                fpngl_noand64, fpngl_noor64));
  }
  fpngl_irng_delete(irng);
}
