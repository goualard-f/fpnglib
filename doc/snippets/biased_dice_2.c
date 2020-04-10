// doc/snippets/biased_dice_2.c
#include <stdio.h>
#include <fpnglib/discrete_distribution.h>
#include <fpnglib/mt19937-64.h>
const uint64_t seed = 42;
const uint32_t ndraws = 1000000;
int main(void)
{
  fpngl_irng_t *irng = fpngl_irng_new64(fpngl_mt19937v64(seed));
  fpngl_distribution_t *dist = fpngl_distribution_new(irng,
                                 (double[]){0.1,0.2,0.1,0.1,0.3,0.2}, 6);
  uint32_t draws[6] = {0,0,0,0,0,0};
  for (uint32_t i = 0; i < ndraws; ++i) {
    draws[fpngl_distribution_next32(dist)]++;
  }
  printf("%.3g %.3g %.3g %.3g %.3g %.3g\n",
         draws[0]/(double)ndraws, draws[1]/(double)ndraws,
         draws[2]/(double)ndraws, draws[3]/(double)ndraws,
         draws[4]/(double)ndraws, draws[5]/(double)ndraws);
  fpngl_distribution_delete(dist);
}
