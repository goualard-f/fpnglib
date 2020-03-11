// doc/snippets/distrib.c
#include <stdio.h>
#include <fpnglib/float64.h>
#include <fpnglib/mt19937-64.h>

const uint64_t seed = 42;

int main(void)
{
  fpngl_irng_t *irng = fpngl_irng_new64(fpngl_mt19937v64(seed));
  fpngl_distribution_t *dist = fpngl_class_float64_new(irng,
                                   (double[]){0.125,0.25,0.5,0.125,0.0});
  for (uint32_t i = 0; i < 10; ++i) {
    printf("%g\n",fpngl_float64_distrib(dist));
  }
  fpngl_distribution_delete(dist);
}
