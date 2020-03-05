// doc/snippets/mcpi.c
#include <stdio.h>
#include <math.h>
#include <fpnglib/frng64_division.h>
#include <fpnglib/mt19937ar.h>
#include <fpnglib/irng_t.h>

#define NITERS 10000000
const uint64_t seed = 13;
const double m_pi = 0x1.921fb54442d18p+1;

// Estimating the value of pi by throwing darts at a unit circle.
double mcpi(fpngl_frng64_t *frng, uint32_t niters)
{
  uint32_t in_circle = 0;
  for (uint32_t i = 0; i < niters; ++i) {
    double x = fpngl_frng64_nextf64(frng);
    double y = fpngl_frng64_nextf64(frng);
    in_circle += ((x*x + y*y) <= 1);
  }
  return 4*((double)in_circle / niters);
}

int main(void)
{
  fpngl_irng_t *irng32 = fpngl_irng_new32(fpngl_mt19937v32(seed));
  fpngl_frng64_t *frng0 = fpngl_bydivision_new("FMT19937v32",irng32,
                                               fpngl_irng_max(irng32)+1);
  fpngl_frng64_t *frng1 = fpngl_drand48bsd(seed);
  printf("%s: %.16g\n",fpngl_frng64_name(frng0), mcpi(frng0,NITERS));
  printf("%s: %.16g\n",fpngl_frng64_name(frng1), mcpi(frng1,NITERS));
  fpngl_frng64_delete(frng0);
  fpngl_frng64_delete(frng1);
}
