// doc/snippets/fsimple.c
#include <stdio.h>
#include <fpnglib/mt19937-64.h>
#include <fpnglib/irng_t.h>
#include <fpnglib/frng64_division_k.h>

const uint32_t seed = 13;

int main(void)
{
  fpngl_frng64_t *frng64 = fpngl_div53(fpngl_irng_new64(
                                         fpngl_mt19937v64(seed)));
  printf("Min: %a, Max: %a\n",
         fpngl_frng64_min(frng64),
         fpngl_frng64_max(frng64));
  printf("%a\n",fpngl_frng64_nextf64(frng64));
  fpngl_frng64_delete(frng64);
}
